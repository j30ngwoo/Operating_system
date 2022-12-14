#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    if(!strcmp(path, name))
      printf("f: %s\n", path);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      //printf("p: %s, buf : %s\n", p, buf);
      //printf("t_%d\n", st.type);
      if(st.type == T_DIR && strcmp(p, ".") && strcmp(p, ".."))
        find(buf, name);
      if(!strcmp(p, name))
        printf("%s\n", buf);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if(argc != 3){
    printf("find : parameter error\n");
    exit();
  }
  find(argv[1], argv[2]);
  exit();
}
