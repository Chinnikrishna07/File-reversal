//#include<bits/stdc++.h>
#include<stdio.h>
#include<string>
#include<fcntl.h>
#include<sys/stat.h>
#include<iostream>
#include<unistd.h>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<cstring>
using namespace std;
void write_str(const char* s){
    write(STDOUT_FILENO,s,strlen(s));
}
void Progress(long long copied, long long total_size) {
    double percent = (double)copied / total_size * 100.0;
     printf("\rProgress: %.2f%%", percent);
     fflush(stdout);
}
bool comapare(vector<char>& in_buf,vector<char>& out_buf,int bytes){
      int i=0;
      for(int i=0;i<bytes;i++){
        if(in_buf[i]!=out_buf[bytes-i-1])
            return false;
      }
      return true;
}
void reverse_section(int fd_i, int fd_o,
                     off_t start, off_t end,
                     ssize_t block_size,
                     off_t &copied, off_t total_size) {
    vector<char> buff(block_size);
    off_t len = end - start ; 
    while (len > 0) {
        size_t bytes = (len >= (off_t)block_size) ? block_size : len;
        lseek(fd_i, end - bytes , SEEK_SET);
        ssize_t red = read(fd_i, buff.data(), bytes);
        reverse(buff.begin(), buff.begin() + red);
        write(fd_o, buff.data(), red);

        copied += red;
        Progress(copied, total_size);

        end -= red;
        len -= red;
    }
}

void flag_1(char* inputfile,int flag){
   
         int fd_i=open(inputfile,O_RDONLY,0644);
         char str[200];
         strcpy(str,"assignment1/1_");
         strcat(str,inputfile);
         int fd_o=open(str,O_CREAT|O_RDWR|O_TRUNC,0600);

         if(fd_o<0 || fd_i<0) perror("open");
         off_t size=lseek(fd_i,0,SEEK_END);
         size_t block_size;
         if(size>static_cast<int64_t>(1024LL*1024LL*1024LL)) block_size=2*1024*1024;
         else block_size=1024;
         vector<char> buff(block_size);
         off_t rem=size;
         off_t prog=0;
         while(rem>0){
            size_t bytes;
            if(rem>=(off_t)block_size){
                  bytes=block_size;
            }
            else 
               bytes=rem;
            off_t offset=rem-bytes;
          lseek(fd_i,offset,SEEK_SET);
          ssize_t red=read(fd_i,buff.data(),bytes);
          reverse(buff.begin(),buff.begin()+red);
          write(fd_o,buff.data(),red);
          //perror("write");
          prog=prog+red;
          Progress(prog,size);
          rem=rem-bytes;
         }
         close (fd_i);
         close (fd_o);
}
void flag_0(char* inputfile,int flag,int block_size){
        char str[200];
        strcpy(str,"assignment1/0_");
        strcat(str,inputfile);
        int fd_i=open(inputfile,O_RDONLY,0644);
        int fd_o=open(str,O_CREAT|O_RDWR|O_TRUNC,0600);
        if(fd_o<0||fd_i<0) {
            perror("open");
            return;
        }
         off_t size=lseek(fd_i,0,SEEK_END);
         if(block_size<0 || block_size==0 ){
            perror("Invalid Block size");
            close(fd_i);
            close(fd_o);
            return;
         }
         lseek(fd_i,0,SEEK_SET);
         vector<char> buff(block_size);
         ssize_t red=size;
         off_t prog=0;
         while(red>0){
            red=read(fd_i,buff.data(),block_size);
            reverse(buff.begin(),buff.begin()+red);
            write(fd_o,buff.data(),red);
            prog=prog+red;
            Progress(prog,size);
            //perror("write");
         }
close(fd_o);
close(fd_i);

}
void flag_2(char* inputfile, int flag, off_t start, off_t end) {
       
         char str[200];
        strcpy(str,"assignment1/2_");
        strcat(str,inputfile);
        int fd_i=open(inputfile, O_RDONLY, 0644);
        int fd_o=open(str, O_CREAT | O_RDWR | O_TRUNC, 0600);
        if(fd_o<0||fd_i<0) {
            perror("open");
            return;
        }
        off_t size = lseek(fd_i, 0, SEEK_END);
         if(start<0 || end<0 || end>=size || start>end || start==size){
            perror("Invalid Indices");
            close(fd_o);
            close(fd_i);
            return;
         }
        lseek(fd_i, 0, SEEK_SET);
        ssize_t block_size;
        if(size >static_cast<int64_t>(1024LL * 1024LL * 1024LL))
            block_size =2 * 1024 * 1024;
        else
            block_size =1024;

        off_t copied =0;

        reverse_section(fd_i, fd_o, 0, start, block_size, copied, size);

        // 2. Copy middle section 
        {
            vector<char> buff(block_size);
            off_t middle_start = start ;
            off_t middle_end = end ;
            if (middle_end >= middle_start) {
                off_t mid_rem = middle_end - middle_start + 1;
                lseek(fd_i, middle_start, SEEK_SET);
                while(mid_rem>0) {
                    size_t bytes =(mid_rem >= (off_t)block_size) ? block_size : mid_rem;
                    ssize_t red =read(fd_i, buff.data(), bytes);
                    write(fd_o, buff.data(), red);

                    copied += red;
                    Progress(copied, size);
                    mid_rem -= red;
                }
            }
        }
        
        reverse_section(fd_i, fd_o, end+1, size, block_size, copied, size);
        cout << "\nDone!\n";
        close(fd_i);
        close(fd_o);
}

int main(int argc , char* argv[]){
    int a=mkdir("assignment1",0700);
    if(a!=0) perror("mkdir failed");
if(argc>=3){
    int flag=*argv[2]-'0';
    if(flag==1 && argc==3){
    flag_1(argv[1],*argv[2]-'0');
    }
    else if(flag==0 && argc==4) {
            flag_0(argv[1],*argv[2]-'0',stoi(string(argv[3])));
        }
    else if(flag==2 && argc==5) {
        flag_2(argv[1],*argv[2]-'0',(off_t)stoi(string(argv[3])),(off_t)stoi(string(argv[4])));
    }
    else{
        perror("Invalid arguments");
        }    //number is large so use stoi
    }
else{
    perror("Invalid arguments");
}
      return 0;
}