#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int a;
int b=0;
char c;
char d='d';

void foobar(){
	int a=10;
	char *b="Vijay";
	printf("Name: %s\n",b);
	int *ptr;
	ptr = (int*)malloc(sizeof(int));
	if (ptr == 0){
		printf("Out of memory\n");
		return;
	}
	*ptr=25;
	printf("Value of ptr:%d\n",*ptr);
	free(ptr);
}

void file_write(char *filename){
	int fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0){
		printf("Error opening file");
		return;
	}
	char * s1="Some test data";
	write(fd,s1, strlen(s1));
	close(fd);
}

void file_read(char * filename){
	int fd = open(filename, O_RDONLY);
	if (fd < 0){
		printf("Error opening file for reading");
		return;
	}
	char c;
	while(read(fd, &c, sizeof(c)) != 0){
		printf("%c", c);
	}
	close(fd);

}

int main(){
	foobar();
	file_write("Testfile1.txt");
	file_read("Testfile1.txt");
	sleep(10);
	return 0;
}

