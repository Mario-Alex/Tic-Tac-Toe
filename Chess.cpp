#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int chess[3][3];
int x,y,count;

int IsWin()
{
	int i;
	for(i=0;i<3;i++)
	{
		if(chess[i][0]==1 && chess[i][1]==1 && chess[i][2]==1) return 1;
		if(chess[i][0]==-1 && chess[i][1]==-1 && chess[i][2]==-1) return -1;
	}

	for(i=0;i<3;i++)
	{
		if(chess[0][i]==1 && chess[1][i]==1 && chess[2][i]==1) return 1;
		if(chess[0][i]==-1 && chess[1][i]==-1 && chess[2][i]==-1) return -1;
	}

	if((chess[0][0]==1&&chess[1][1]==1&&chess[2][2]==1)||(chess[2][0]==1&&chess[1][1]==1&&chess[0][2]==1)) return 1;
    if((chess[0][0]==-1&&chess[1][1]==-1&&chess[2][2]==-1)||(chess[2][0]==-1&&chess[1][1]==-1&&chess[0][2]==-1)) return -1;

	return 0;
}

int Evaluation()
{
	int i,j,temp[3][3];

	x=y=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=1;
			else temp[i][j]=chess[i][j];
		}
	}
 
	for(i=0;i<3;i++)
	{
		x+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{
		x+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	x+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	x+=(temp[2][0]+temp[1][1]+temp[0][2])/3;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=-1;
			else temp[i][j]=chess[i][j];
		}
	}


	for(i=0;i<3;i++)
	{
		y+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{
		y+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	y+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	y+=(temp[2][0]+temp[1][1]+temp[0][2])/3;

	return x+y;
}

int AlphaBeta(int &value,int deep,bool MAX)
{
	bool prune=false;
	int i,j,flag,temp;        
     
    if(deep==3||deep+count==9)
    {
        return Evaluation();
    }
                
    if(IsWin()==1)
    {
        value=10000;
        return 0;
    }

    if(MAX)                  
        flag=10000;
    else
        flag=-10000;
    for(i=0;i<3 && !prune;i++)
    {
        for(j=0;j<3 && !prune;j++)
        {
            if(chess[i][j]==0)
            {
                if(MAX)
                {
                    chess[i][j]=-1;
                        
                    if(IsWin()==-1)
                        temp=-10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp<flag) flag=temp;                      
                    if(flag<=value) prune=true;                      
                }
                else
                {
                    chess[i][j]=1;
                    
                    if(IsWin()==1)
                        temp=10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp>flag) flag=temp;                     
                    if(flag>=value) prune=true;
                       
                }
                chess[i][j]=0;
            }
        }
    }
    if(MAX)
    {
        if(flag>value)
            value=flag;
    }
    else
    {
        if(flag<value)
            value=flag;
    }


    return flag;
}

void PlayerInput()
{
	int row,col;
	while(true)
	{
		printf("\nYou move it at(x y):");
		scanf("%d%d",&row,&col);

		if(row>0&&row<4&&col>0&&col<4&&chess[row-1][col-1]==0)
		{
			chess[row-1][col-1]=-1;
			break;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
}

void PrintChess()
{
	int i,j;

	printf("\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==1) printf("¡ð");
			if(chess[i][j]==0) printf("¡õ");
			if(chess[i][j]==-1) printf("¡Á");
		}
		printf("\n");
	}
}

int PlayChess()
{
	int row,col,temp;
	int m=-10000,value=-10000,deep=1;
 
	count=0;
	memset(chess,0,sizeof(chess));
	printf("ChessBoard:\n");
	PrintChess();

	while(true)
	{
		printf("\nWho take the first step:\n1)Player.  2)Computer.[ ]\b\b");
		scanf("%d",&temp);
		if(temp!=1 && temp!=2) getchar();
		else break;
	}

	if(temp==1)
	{ 
		while(true)
		{
			PlayerInput();
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
			if (IsWin()==-1)
			{
				printf("\nCongratulations,you win!\n");
				return 0;
			}

			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(chess[i][j]==0)
					{
						chess[i][j]=1;
						AlphaBeta(value,deep,1);

						if(IsWin()==1)  
						{
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m) 
						{
							m=value;
							row=i;col=j;
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			if(chess[row][col])
			{
				printf("\nCongratulations,you win!\n");
				return 0;
			}
			chess[row][col]=1;
	   
			value=-10000;m=-10000;deep=1;
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
		}
	}
	else                                                           
	{
		while(true)
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(chess[i][j]==0)
					{
						chess[i][j]=1;
						AlphaBeta(value,deep,1);

						if(IsWin()==1)  
						{
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m) 
						{
							m=value;
							row=i;col=j;
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			chess[row][col]=1;
	   
			value=-10000;m=-10000;deep=1;
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(x==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
				
			PlayerInput();
			PrintChess();
			count++;
			Evaluation();
			
			if(x==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}

			if (IsWin()==-1)
			{
				printf("\nCongratulations,you win!.\n");
				return 0;
			}
		}
	}
	
	return 0;
}

void main()
{
	int k;
	while(true)
	{
		PlayChess();
		printf("\nTry Again?\n1)Yeah.\t2)Exit.[ ]\b\b");
		scanf("%d",&k); 
		if(k!=1 && k!=2) getchar();
		if(k==2) break;
	}
}
