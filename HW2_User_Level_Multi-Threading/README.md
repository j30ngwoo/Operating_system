## Lab2: User Level Multi-Threading

### 1. RISC-V Assembly questions
#### 1) Which registers contain arguments to functions? For example, which register holds 13 in main's call to printf?

a0 – a7 레지스터가 Function arguments 역할을 한다.
13은 li(load immediate) a2, 13 이므로 a2 레지스터에 들어 있다.  

#### 2) Where is the function call to f from main? Where is the call to g? (Hint: the compiler may inline functions.)
 
f함수는 li a2,13에서 호출된다.
g함수는 f함수 내의 return g(x);에서 호출되므로
addiw a0,a0,3에서 처음으로 호출된다.  

#### 3) At what address is the function printf located?
 
Call.asm에서는 주소 650에 printf가 위치한 것을 볼 수 있다.
 
Main을 봤을 때, 
auipc	ra, 0x0		->  ra == 0x30
jalr	1568(ra)		->  0x30 + 1568 = 1616 = 0x650  

#### 4) What value is in the register ra just after the jalr to printf in main?
jalr 당시의 PC가 34이므로, 34 + 4인 38을 ra에 저장한다.  

### 2. uthread

#### Quick explanation
 
각 쓰레드에 레지스터를 할당해주기 위한 context 구조체입니다. Address를 return하는 ra, stack pointer 역할을 해주는 sp, 그리고 callee-saved register s0부터 s11까지로 구성되어 있습니다.

CPU 할당을 위해 context 구조체인 scheduler를 thread 구조체에 추가해주었습니다.

Thread_schedule()에서는 현재 쓰레드를 기준으로 모든 쓰레드를 돌며 상태를 확인합니다. RUNNABLE인 쓰레드를 발견하면 next_thread를 갱신합니다. Next_thread 0 그대로라면 어떤 쓰레드도 실행 불가이므로 메시지를 출력하고 종료합니다. 현재 쓰레드와 next_thread가 다르다면, next_thread의 상태를 RUNNING으로 갱신하고, 현재 쓰레드를 t에 저장합니다. 그 후, thread_switch 함수를 이용해 각 쓰레드의 레지스터 값을 switch합니다(context switching). 

Thread_create_(void (*func)()) 함수는 새로운 thread를 생성합니다. while문을 이용해 state가 FREE인 쓰레드 구조체를 발견하면, RUNNABLE로 상태를 바꿔주고, scheduler 구조체의 레지스터 값을 모두 0으로 초기화합니다. 그 후 ra에는 매개변수로 받은 함수의 주소 (예 : thread_a)를 넣어주고, sp에는 스택 주소에서 MAX STACK SIZE만큼 확보하여 전달합니다.