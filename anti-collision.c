#include<stdio.h>
int tag [4][10]={ 1,0,1,1,0,0,1,0,0,0,
                 1,0,1,0,0,0,1,1,0,0,
	             1,0,1,1,0,0,1,1,0,0,
	             1,1,1,0,0,0,1,1,0,0};
int list[8]={1,1,1,1,1,1,1,1};
int list1[8]={1,1,1,1,1,1,1,1};
void compare(int b []){
	for(int i=0;i<4;i++){
		if(tag[i][8]!=1){
		 for(int j=0;j<8;j++){
		     if(b[j]-tag[i][j]>=0){
		      tag[i][8]=1;
			 }
			 else {
				 tag[i][8]=0;
				 break;
			 }
		  }
		} 
	}
}
void print(int j){
	printf("标签:");
	for(int i=0;i<8;i++)
	{
	printf("  %d",tag[j][i]);
	}	
	printf("\n");
}

void find(int i,int j){
	if(j==8){

		compare(list);
		for(i=0;i<4;i++)
		{
			if(tag[i][8]==1&&tag[i][9]==0)
			{ 
			  print(i);
			  tag[i][9]=1;
			}
		}
		return ;
	}
	for(i=i+1;i<4;i++){
		if(tag[i][j]!=tag[i-1][j]) break;
	}
	if(i==4) find(0,j+1);
	else if(i<4) {
		list[j]=0;
		find(0,j+1);
		list[j]=1;
		find(0,j+1);
	}

}
void findlist(){
	for(int i=1;i<4;i++){
		if(tag[i][8]==0){
			for(int j=0;j<8;j++){
				if(tag[i][8]==1)
				{
			    if(tag[i][j]-tag[i-1][j]!=0)
					list[j]=0;
				}
			}
		}	
	}

}

int main(){
	int number=4;
	
	while(number>0){
		 printf("待识别的标签：\n");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<8;j++)
			{
			printf("  %d",tag[i][j]);
			}
			printf("\n");
		}

		printf("\n");
		find(0,0);
		compare(list1);
	   
		for( i=0;i<4;i++)
		{
			if(tag[i][9]==1)
			{ 
			  number--;
			}
		}
		
	};
    return 0;
}
