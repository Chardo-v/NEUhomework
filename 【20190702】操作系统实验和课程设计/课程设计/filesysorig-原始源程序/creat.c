/*	文件创建函数creat()(creat.c)*/
#include <stdio.h>
#include "filesys.h"
creat(user_id, filename, mode)
unsigned int user_id;
char * filename;
unsigned short mode;
{
	unsigned int di_ith, di_ino;
	struct inode * inode;
	int i,j;
	di_ino=namei(filename);  // ???
	if (di_ino!=NULL)	/* already existed */
	{
		inode=iget(di_ino);
		if (access(user_id, inode, inode)==0)
			{
			iput(inode);
			printf ("\rcreat access not allowed \n");
			return -1;
		}
	/* free all the block of the old file */
	for(i=0;i<inode->di_size/BLOCKSIZ+1; i++)
	{
		bfree(inode->di_addr[i]);
	}

	/* to do: add code here to update the pointer of the sys_file */
	for (i=0;i<SYSOPENFILE;i++)
		if (sys_ofile[i].f_inode == inode)
		{
			sys_ofile[i].f_off=0;
		}
	for (i=0; i<NOFILE; i++)
		if (user[user_id].u_ofile[i]==SYSOPENFILE+1)
			{
				user[user_id].u_uid=inode->di_uid;
				user[user_id].u_gid=inode->di_gid;
				for (j=0; j<SYSOPENFILE; j++)
					if (sys_ofile[j].f_count==0)
					{
						user[user_id].u_ofile[i]=j;
						sys_ofile[j].f_flag=mode;
					}
				return i;
			}
	}
	else /* not existed before */
	{
		inode = ialloc();
		di_ith=iname(filename);
		dir.size++;

		dir.direct[di_ith].d_ino=inode->i_ino;

		inode->di_mode = user[user_id].u_default_mode;
		inode->di_uid = user[user_id].u_uid;
		inode->di_gid=user[user_id].u_gid;
		inode->di_size=0;
		inode->di_number= 0;

		for(i=0;i<SYSOPENFILE;i++)
			if (sys_ofile[i].f_count==0)
			{
				break;
			}

		for (j=0; j<NOFILE; j++)
			if (user[user_id].u_ofile[j]==SYSOPENFILE+1)
			{
				break;
			}
		user[user_id].u_ofile[j]=i;
		sys_ofile[i].f_flag=mode;
		sys_ofile[i].f_count=0;
		sys_ofile[i].f_off=0;
		sys_ofile[i].f_inode=inode;
		return j;
	}
	return -1;  //????
}