#include "myext2.h"
#include <stdio.h>
#include <string.h>

#define FILE_PATH "myfs"

int main ()
{
	struct ext2_super_block *SB;
	
	FILE *fd = NULL;
	//char buff[1024]="";
	//memset(buff, 0, sizeof(buff));
	//char *buff = NULL;
	SB = (struct ext2_super_block*) malloc(sizeof(struct ext2_super_block));

	printf("buff size:%d", sizeof(struct ext2_super_block));

	fd = fopen(FILE_PATH, "rw+");
	
	if(fd == NULL)
	{
		perror("Could not open file.");
		return 2;
	}

	if(0 != fseek(fd, 1024, SEEK_CUR))
	{
		perror("fseek error.");
		return 3;
	}
printf("Reading...\n");
	//size_t result = fread(buff, 1, sizeof(buff)*1024, fd);
	size_t result = fread(SB, 1, sizeof(struct ext2_super_block), fd);
	if(result != sizeof(struct ext2_super_block))
	{
		perror("Read error");
		return 4;
	}
printf("Read complete...\n");
	//SB = (struct xt2_super_block*) buff;

	printf("Magic num = %hx\n", SB->s_magic);
	printf("OS = %hx\n", SB->s_creator_os);
	printf("s_inodes_count = %hx\n", SB->s_inodes_count);
	printf("s_blocks_count = %hx\n", SB->s_blocks_count);
	printf("s_uuid = ");
	int i;
	for(i=0; i<16; i++)
	{
		printf("%hx",SB->s_uuid[i]);
	}
	printf("\ns_volume_name = %16s\n", SB->s_volume_name);
	printf("s_log_block_size = %hx\n", SB->s_log_block_size);

	fclose(fd);

	return 0;
}
