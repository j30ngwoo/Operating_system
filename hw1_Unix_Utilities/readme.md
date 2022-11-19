## OS HW1 - Unix Utilities

### 1. Sleep
main함수의 parameter로 sleep과 정수형태의 문자열을 받습니다. 만약 parameter의 개수가 2개가 아닐 경우, 오류를 출력합니다. Argv의 index 1에 들어 있는 문자열을 정수로 사용하기 위해, atoi 함수를 사용하여 문자열을 정수로 변환시켜줍니다. 변환시킨 정수 틱 만큼 syscall sleep을 호출하여 사용한 후 main함수를 종료합니다.

### 2. Pingpong
fd1, fd2라는 2칸짜리 int형 배열을 만듭니다. 이 fd들을 pipe로 지정해줍니다.  
 
Fork를 통해 return값인 pid를 받습니다. Pid가 0일 경우 child process이고, 아닐 경우 parent process가 실행될 수 있게 if문을 설정합니다. Pingpong함수의 진행 순서는 다음과 같습니다.
> 1.	Parent process에서 fd1 pipe의 1번 인덱스로 ping을 write합니다.
> 2.	Child process에서 fd1 pipe의 0번 인덱스로 ping을 read하여 buf에 저장합니다.
> 3.	Getpid를 통해 child 본인의 pid를 얻고, buf에 입력된 ping과 함께 출력합니다.
> 4.	Child process에서 fd2 pipe의 1번 인덱스로 pong을 write한 후 종료합니다.
> 5.	Parent process에서 fd2 pipe의 0번 인덱스로 pong을 read합니다.
> 6.	Getpid를 통해 parent 본인의 pid를 얻고, buf에 입력된 pong과 함께 출력한 후 종료합니다.

### 3. Find
Main parameter로 3개를 받고, 아닐 경우 오류를 출력합니다. Argv[1]는 path, argv[2]는 file name to find로 받아 find함수를 실행합니다. 먼저 path에 해당되는 요소를 open하여 리턴 값인 file descriptor를 fd에 넣습니다. 그 후 해당 fd의 stat을 "kernel/stat.h"를 통해 선언된 struct stat인 st에 넣습니다. st.type에 들어있는 해당 fd의 type에 따라 명령을 실행하기 위해, switch case문을 실행합니다. 
Type이 T_FILE일 경우, 현재 find함수에 주어진 path가 file이라는 뜻이고, 더 실행할 필요가 없으니 path와 name을 비교하여 출력 후 종료합니다.
Type이 T_DIR일 경우, path가 디렉토리라는 뜻이고, 해당 디렉토리 내의 요소들을 파악하기 위해 struct dirent de에 모든 요소들을 read한 후, stat을 통해 st에 해당 요소의 stat을 받습니다. 
> 1.	해당 요소의 type이 T_DIR이면서 .(해당 디렉토리)이나 ..(상위 디렉토리)이 아닐 경우 하위 디렉토리이므로, find함수에 해당 하위 디렉토리의 path를 넘겨주어 재귀합니다. 
> 2.	해당 요소의 type이 T_DIR이 아니고, name과 이름이 같을 경우, 출력한 후 종료합니다.

### 4. Xargs
받은 요소들을 하나의 exec함수로 실행하기 위해, 4 x 1000의 2차원 배열인 **arr를 선언한 후 malloc하였습니다. Arr의 각 index의 역할은 다음과 같습니다.
Arr[0] : argv[1]
Arr[1] : argv[2]부터 마지막 argv[index] 까지.
Arr[2] : 2번째, 3번째, 4번째 … 줄의 문자열이 들어갈 위치.
Arr[3] : NULL pointer.
예를 들어, 
Input : xargs echo hi hello \n 0123 4567 (EOF)일 때, 
Arr[0] : “echo”, arr[1] : “hi hello”, arr[2] : “0123 4567”, arr[3] : NULL 가 됩니다.
35번째 줄까지는 argv로 받은 인자들을 arr[0], arr[1]에 넣어줍니다. 그 후 while문에서는 개행을 기준으로 각 줄을 읽습니다. 각 줄이 들어올 때마다, arr[2]에 넣고(갱신하고), fork후 exec을 통해 실행합니다. EOF가 read되었을 경우, exit을 통해 main함수를 종료합니다.
  
 
종료하기 전 malloc했던 arr를 free하고, exit합니다.

감사합니다 ^_^
