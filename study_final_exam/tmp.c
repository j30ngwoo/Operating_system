바운디드 버퍼
mutex = 1
full = 0;
empty = n;

reader
wait(full)
wait(m)
sig(m)
sig(empty)


리더 라이터
mutex
mutexrw
cnt;

writer
wait(mtxrw)

reader
wait(m)
c++;
if(c==1)
	wait(rw);
sig(m)

wait(m)
c--;
if(c==0)
	sig(rw);
sig(m)


철학자
state = 띵, 헝, 이팅
conditong self[i]

pickup
state = h;
test;
if (state != e)
	self[i].wait()

pickdown
state = t;
test[i + 4 % 5]
test[i + 1 % 5]

test;
if !e im h
state=e
self[i].sig