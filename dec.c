#include<stdio.h>
#include<string.h>

void analyse(char buf1,char buf2,long count)
{
    static unsigned int old_diff=0;
    
    unsigned int diff;
    
    diff=((buf1&0xFF) - (buf2&0xFF)&0xFF);
    
    if(old_diff != diff)
    {
        //if(diff == -255)
            //printf("a %X,b %X,x %X.\n",buf1,buf2,diff);
        printf("diff at %ld,value %d.\n",count,diff);
        
        printf("input %d,output %d.\n",buf1,buf2);
        
        old_diff = diff;
    }
}


int main(void)
{
    FILE *stream_in;
    FILE *stream_out;
    char buf1,buf2;
    long count=0;
    unsigned long filesize = -1; 
    
    if((stream_in=fopen("input","r"))==NULL)
    {
        fprintf(stderr,"Can not open input file.\n");
        return 0;
    }
    if((stream_out=fopen("output","r"))==NULL)
    {
        fprintf(stderr,"Can not open output file.\n");
        fclose(stream_in);
        return 0;
    }
    
    
    fseek(stream_in, 0L, SEEK_END);  
    filesize = ftell(stream_in);
	fseek(stream_in,0,SEEK_SET);
    
    printf("file_size:%ld.\n",filesize);
    
    /*sizeof（char）=1 seek to the beginning of the file*/
    //fseek(stream_in,0,SEEK_SET);
    //fseek(stream_out,0,SEEK_SET);
    
    while(!feof(stream_in))
    {
        if(feof(stream_out))
        {
            fprintf(stderr,"File out do not match.\n");
            break;
        }
        
        fread(&buf1,1,1,stream_in);
        fread(&buf2,1,1,stream_out);
        
        count++;
        
        analyse(buf1,buf2,count);
    }
    
    if(!feof(stream_out))
    {
        fprintf(stderr,"File in do not match.\n");
    }
    
    printf("end at %ld.\n",ftell(stream_in));
    fclose(stream_in);
    fclose(stream_out);
    return 0;
}