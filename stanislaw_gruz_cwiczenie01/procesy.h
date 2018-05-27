#ifndef HEADER_PROCESY
#define HEADER_PROCESY


void showProcessInfo(){
uid_t uid = getuid();
gid_t gid = getgid();
pid_t pid = getpid();
pid_t ppid = getppid();
pid_t pgid = getpgid(pid);


printf("UID = %d\tGID = %d\tPID = %d\tPPID = %d\tPGID = %d\n",uid,gid,pid,ppid,pgid);
}


#endif // HEADER_PROCESY
