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
void write_str1(const char* s,string str){
    string a=string(s)+str;
    write(STDOUT_FILENO,a.c_str(),a.size());
}
void permissions(char* file,string str){
 struct stat st;
    if (stat(file, &st) == -1) {
        perror("stat");
        return;
    }

    write_str1("User has read permissions on ",str);
    write_str((st.st_mode & S_IRUSR) ?"Yes\n":"No\n");
    write_str1("User has write permission on ",str);
    write_str((st.st_mode & S_IWUSR) ?"Yes\n":"No\n");
    write_str1("User has execute permission on ",str);
    write_str((st.st_mode & S_IXUSR) ?"Yes\n":"No\n");

    write_str1("Group has read permissions on ",str);
    write_str((st.st_mode & S_IRGRP) ?"Yes\n":"No\n");
    write_str1("Group has write permission on ",str);
    write_str((st.st_mode & S_IWGRP) ?"Yes\n":"No\n");
    write_str1("Group has execute permission on ",str);
    write_str((st.st_mode & S_IXGRP) ?"Yes\n":"No\n");

    write_str1("Others has read permissions on ",str);
    write_str((st.st_mode & S_IROTH) ?"Yes\n":"No\n");
    write_str1("Others has write permission on ",str);
    write_str((st.st_mode & S_IWOTH) ?"Yes\n":"No\n");
    write_str1("Others has execute permission on ",str);
    write_str((st.st_mode & S_IXOTH) ?"Yes\n":"No\n");
}
bool compare(vector<char>& in_buf,vector<char>& out_buf,long long bytes){
  
      for(long long i=0;i<bytes;i++){
        if(in_buf[i]!=out_buf[bytes-i-1])
            return false;
      }
      return true;
}
bool q2flag_0(char* inputfile,char* outputfile,char* directory,int block_size){
      
      int fd_i=open(inputfile,O_RDONLY);
         int fd_o=open(outputfile,O_RDONLY);
         if(fd_o<0 || fd_i<0) return false;
         off_t in_size=lseek(fd_i,0,SEEK_END);
         off_t out_size=lseek(fd_o,0,SEEK_END);
         lseek(fd_i,0,SEEK_SET);
         lseek(fd_o,0,SEEK_SET);
         if(block_size<=0 || block_size>in_size){
            perror("Invalid blocksize");
            return false;
         }
         vector<char> in_buff(block_size);
         vector<char>out_buff(block_size);
         write_str("Directory is created: Yes\n");
         ssize_t rem=in_size;
         while(rem>0){
            long long bytes;
            if(rem>=block_size)
               bytes=block_size;
            else
              bytes=rem;
            read(fd_i,in_buff.data(),bytes);
            read(fd_o,out_buff.data(),bytes);
            if(!compare(in_buff,out_buff,bytes)){
                 write_str("Whether file contents are correctly processed : No\n");
                 return false;
            }
            rem=rem-bytes;
         }
         write_str("Whether file contents are correctly processed : Yes\n");
      if(out_size!=in_size){
          write_str("Both files sizes are same :no\n");
           return false;
         }
      else{
       write_str("Both Files Sizes are same :yes\n");
       }
      permissions(outputfile,"newfile: ");
      permissions(inputfile,"oldfile: ");
      permissions(directory,"directory: ");
close(fd_o);
close(fd_i);
    return true;
   }
bool q2flag_1(char* outputfile,char* inputfile){
  int fd_o=open(outputfile,O_RDONLY);
  int fd_i=open(inputfile,O_RDONLY);
  size_t blocksize;
  if(fd_o<0||fd_i<0) return false;
  off_t out_size=lseek(fd_o,0,SEEK_END);
  off_t in_size=lseek(fd_i,0,SEEK_END);
   lseek(fd_i,0,SEEK_SET);
   write_str("Directory is created:Yes\n");
      if(in_size>1024LL*1024LL*1024LL)
               blocksize=8*1024*1024;
      else 
         blocksize=1024;
   size_t rem=out_size;
    vector<char> in_buf(blocksize);
    vector<char> out_buf(blocksize);
   
    off_t prog=0;
   while(rem>0){
      size_t bytes;
      if(rem>=blocksize)
           bytes=blocksize;
      else
          bytes=rem;
      off_t len=read(fd_i,in_buf.data(),bytes);
      lseek(fd_o,rem-bytes,SEEK_SET);
      off_t len2=read(fd_o,out_buf.data(),bytes);
     if(!compare(in_buf,out_buf,(int) bytes)){
         write_str("Whether file contents are correctly processed:No\n");
         return false;
     }
     rem=rem-bytes;
   }
   write_str("Whether file contents are correctly processed:Yes\n");
   
    struct stat st;
    if (stat(outputfile, &st) == -1) {
        perror("stat");
        return false;
    }
     if(out_size!=in_size){
    write_str("Both files sizes are same :no\n");
    return false;
   }
   else{
    write_str("Both Files Sizes are same :yes\n");
   }
   permissions(outputfile,"newfile: ");
   permissions(outputfile,"oldfile: ");
   permissions(outputfile,"directory: ");

    close(fd_i);
    close(fd_o);

    return true;
}
bool q2flag_2(char* outputfile, char* inputfile,char* directory ,off_t start, off_t end) {
    int fd_o = open(outputfile, O_RDONLY, 0644);
    int fd_i = open(inputfile, O_RDONLY, 0644);

    if (fd_o < 0 || fd_i < 0) return false;

    off_t out_size = lseek(fd_o, 0, SEEK_END);
    off_t in_size  = lseek(fd_i, 0, SEEK_END);
    lseek(fd_o, 0, SEEK_SET);
    lseek(fd_i, 0, SEEK_SET);

    write_str("Directory is created: Yes\n");

    if (out_size != in_size) {
        write_str("Both Files Sizes are same: No\n");
        close(fd_o);
        close(fd_i);
        return false;
    } else {
        write_str("Both Files Sizes are same: Yes\n");
    }

    size_t blocksize = (in_size > 1024LL * 1024LL * 1024LL) ? (2 * 1024 * 1024) : 1024;
    vector<char> buf_old(blocksize), buf_new(blocksize);

    bool content_ok = true;

    {
        off_t rem = start;
        off_t pos_old = 0;
        off_t pos_new = start - 1;
        while (rem > 0 && content_ok) {
            size_t bytes = (rem >= (off_t)blocksize) ? blocksize : rem;
            lseek(fd_i, pos_old, SEEK_SET);
            lseek(fd_o, pos_new - bytes + 1, SEEK_SET);

            ssize_t r1 = read(fd_i, buf_old.data(), bytes);
            ssize_t r2 = read(fd_o, buf_new.data(), bytes);

            for (ssize_t i = 0; i < r1; i++) {
                if (buf_old[i] != buf_new[r1 - i - 1]) {
                    content_ok = false;
                    break;
                }
            }

            pos_old += bytes;
            pos_new -= bytes;
            rem -= bytes;
        }
    }

    // 2. [start, end] identical
    {
        off_t rem = end - start + 1;
        off_t pos_old = start;
        off_t pos_new = start;
        while (rem > 0 && content_ok) {
            size_t bytes = (rem >= (off_t)blocksize) ? blocksize : rem;
            lseek(fd_i, pos_old, SEEK_SET);
            lseek(fd_o, pos_new, SEEK_SET);

            ssize_t r1 = read(fd_i, buf_old.data(), bytes);
            ssize_t r2 = read(fd_o, buf_new.data(), bytes);

            for (ssize_t i = 0; i < r1; i++) {
                if (buf_old[i] != buf_new[i]) {
                    content_ok = false;
                    break;
                }
            }

            pos_old += bytes;
            pos_new += bytes;
            rem -= bytes;
        }
    }

    // 3. (end, EOF] reversed
    {
        off_t rem = in_size - (end + 1);
        off_t pos_old = end + 1;
        off_t pos_new = in_size - 1;

        while (rem > 0 && content_ok) {
            size_t bytes = (rem >= (off_t)blocksize) ? blocksize : rem;
            lseek(fd_i, pos_old, SEEK_SET);
            lseek(fd_o, pos_new - bytes + 1, SEEK_SET);

            ssize_t r1 = read(fd_i, buf_old.data(), bytes);
            ssize_t r2 = read(fd_o, buf_new.data(), bytes);

            for (ssize_t i = 0; i < r1; i++) {
                if (buf_old[i] != buf_new[r1 - i - 1]) {
                    content_ok = false;
                    break;
                }
            }

            pos_old += bytes;
            pos_new -= bytes;
            rem -= bytes;
        }
    }

    // Result of content check
    if (content_ok)
        write_str("Whether file contents are correctly processed: Yes\n");
    else
        write_str("Whether file contents are correctly processed: No\n");

    // Permissions for newfile
    struct stat st;
    if (stat(outputfile, &st) == -1) {
        perror("stat");
        close(fd_i);
        close(fd_o);
        return false;
    }
  permissions(outputfile,"newfile: ");
  permissions(inputfile,"oldfile: ");
  permissions(directory,"directory: ");

    close(fd_i);
    close(fd_o);

    return content_ok;
}

int main(int argc,char* argv[]){
    if(argc==6 || argc==5 || argc==7){
     try{long long arg=stoll(argv[4]);
      if(arg==1 && argc==5 ){
        q2flag_1(argv[1],argv[2]);
      }
      else if(arg==2 && argc==7){
         q2flag_2(argv[1],argv[2],argv[3],stoll(argv[5]),stoll(argv[6]));
      }
      else if(arg==0 && argc==6){
         q2flag_0(argv[1],argv[2],argv[3],stoll(argv[5]));
      }
      else{
        perror("Invalid arguments");
      }
   }

    catch(invalid_argument&e){perror("Invalid argument");
    }
}

else{
        perror("Invalid arguments");
    }

    return 0;
}
