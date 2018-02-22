#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>  

int CreateDir(const char *sPathName)
{
	char DirName[256];
	strcpy(DirName,sPathName);
	int i,len=strlen(DirName);
	if (DirName[len - 1] != '/')
		strcat(DirName,"/");

	len=strlen(DirName);

	for (i = 1;i < len;i++)
	{
		if (DirName[i] == '/')
		{
			DirName[i]=0;
			if (access(DirName, F_OK) != 0)
			{
				if (mkdir(DirName,0755) == -1)
				{
					perror("mkdir error");
					return -1;
				}
			}
			DirName[i]='/';
		}
	}

	return 0;
}

unsigned char decode(unsigned char input)
{
	unsigned char output;
	
	output= ((input & 0xFF) - 1) & 0xFF;
	
	return output;
}


void convert(char *in_path,char *out_path)
{	
	FILE *stream_in;
    FILE *stream_out;
    char buf1,buf2;
	unsigned long filesize = -1; 
	
	if((stream_in=fopen(in_path,"r"))==NULL)
    {
        fprintf(stderr,"Can not open input file %s.\n",in_path);
        return ;
    }
	
	if((stream_out=fopen(out_path,"w"))==NULL)
    {
        fprintf(stderr,"Can not open output file %s.\n",out_path);
		fclose(stream_in);
        return ;
    }
	
	fseek(stream_in, 0L, SEEK_END);  
    filesize = ftell(stream_in);
	fseek(stream_in,0,SEEK_SET);
	
	while(ftell(stream_in) < (filesize - 3))
    {
        fread(&buf1,1,1,stream_in);
		
		buf2 = decode(buf1);
		
        fwrite(&buf2,1,1,stream_out);
    }
	
	fclose(stream_in);
    fclose(stream_out);
	
	//fprintf(stdout,"Convert file %s to %s.\n",in_path,out_path);
}

void list(char *in_path,char *out_path)
{
	struct dirent* ent = NULL;
    DIR *pDir;
	char buff1[256],buff2[256];
	
	fprintf(stdout,"entering dir:%s\n",in_path);
	
	CreateDir(out_path);
	
    pDir=opendir(in_path);
    while (NULL != (ent=readdir(pDir)))
    {
		if (ent->d_type==8)
		{
			sprintf(buff1,"%s/%s",in_path,ent->d_name);
			sprintf(buff2,"%s/%s.mp3",out_path,ent->d_name);
			fprintf(stdout,"Convert file %s to %s.\n",buff1,buff2);
			convert(buff1,buff2);
		}
		else if (ent->d_type==4)
		{
			if(ent->d_name[0] != '.')
			{
				sprintf(buff1,"%s/%s",in_path,ent->d_name);
				sprintf(buff2,"%s/%s",out_path,ent->d_name);			
				list(buff1,buff2);
			}
		}
    }
	fprintf(stdout,"exit dir:%s\n",out_path);
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr,"Too few input arg.\n");
		return -1;
	}
	if(access(argv[1], F_OK)!= 0)
	{
		fprintf(stderr,"Error input arg.\n");
		return -1;
	}
	list(argv[1],argv[2]);
	return 0;
}