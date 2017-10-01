#include "stdio.h"
#include "stdlib.h"//system("cls");srand(seed);
#include "time.h"//time(NULL);
#include "conio.h"//getch
#include "stdbool.h"//只是更语义化，c用0,1完全就够了。
#include <unistd.h>//sleep(int second);

//全局二维数组定义
int table[4][4];

bool flagNum1,flagNum2,flagNum3,flagNum4;//判断四个方向的可移动性标志
bool flagNum;//是否能出现新的数字标志，false代表当前操作即无移动有无合并

//移动测试数组
// int table[4][4] ={
// 	{2,2,2,2},
// 	{0,2,2,2},
// 	{0,4,2,2},
// 	{2,0,4,2}
// };
// int table[4][4] ={
// 	{0,4,0,4},
// 	{0,0,0,0},
// 	{0,4,0,0},
// 	{0,0,0,0}
// };
// int table[4][4] ={
// 	{256,4,128,4},
// 	{128,2,4,8},
// 	{2,4,8,16},
// 	{4,128,64,32}
// };



//函数声明
void displayTable();
void init();
void placeNumber();
void oneMove();
void moveAble();

int main(int argc, char const *argv[])
{
	init();

	while(true)
	{
//todo
//		printf("11111111111\n");
		moveAble();
//		printf("11111111111\n");

		//测试预测代码是否达到预期
//		printf("flagNum1= %d,flagNum2= %d,flagNum3= %d,flagNum4= %d",flagNum1,flagNum2,flagNum3,flagNum4);
//		bool类型变量在打印时只能用%d，0or1形式输出

		if ((flagNum1 || flagNum2 || flagNum3 || flagNum4)==false)//四个方向都不可移，就代表肯定满了
		{
			printf("You lose!\n");
			sleep(4);
			break;
		}

		oneMove();
		if (flagNum)
		{
//			sleep(2);//进程睡2s，易于观察
			placeNumber();
		}

		

	}
	return 0;
}

void init()
{
	//所有数组里面数字初始化为0
	//移动测试时候注释掉
	int i,j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			table[i][j] = 0;
		}
	}

	srand((unsigned)time(NULL));//必须只有一个！否则每次种子值大致相同，随机数会相同
	placeNumber();//初始化第一个点
	placeNumber();//初始化第二个点
	//测试时注释

	//测试时必写
//	displayTable();
}

void displayTable()
{
	int i,j,k;
	system("cls");//屏幕清屏，每次重新显示当前方格
	for (i = 0; i < 12; ++i)
	{
		printf(" _");
	}
	printf("\n");

	
	for (i = 0; i < 4; ++i)
	{
		printf("|");
		for (j = 0; j < 4; ++j) {
			if (table[i][j] == 0)//待：是零不显示
			{
				printf("     ");//5个空格
			}else
			{
				printf("%5d",table[i][j]);
			}
			
			printf("|");
		}
	
		printf("\n");

		for (k = 0; k < 12; ++k)
		{
			printf(" _");
		}
		printf("\n");
	}
}

void placeNumber()
{
	while(true)//数组值非零重新求取！
	{
		int index =	rand()%16;
		int num = (rand()%2+1)*2;
		if (table[index/4][index%4] == 0)
		{
			table[index/4][index%4] = num;
			break;
		}
	}
	displayTable();	
}


void moveAble()
{
	int i,j,z,m,k;
	flagNum1 = false;
    flagNum2 = false;
    flagNum3 = false;
    flagNum4 = false;

    //上
    	for (j = 0; j < 4; ++j)
		{
			//合并
		  	for (i = 0; i < 4; ++i)
		  	{
		  		if (table[i][j] !=0 && i != 3)
		  		{
		  			for (z = i+1; z < 4; ++z)
		  			{
		  				if (table[i][j] != table[z][j] && table[z][j] !=0)
		  				{
		  					break;
		  				}
		  				if (table[i][j] == table[z][j])
		  				{
		  					flagNum1 = true;
		  					break;
		  				}
		  			}
		  		}
		  	}

		  	//移动
		  	for (m = 0; m < 4; ++m)
		  	{
		  		if (table[m][j] == 0)
		  		{
		  			break;
		  		}
		  	}
	//此时m为第一个空位，如果后面有非零元素，则一定可移动!
		  	for (k = m+1; k < 4; ++k)
		  	{	
		  		if(table[k][j] !=0 )
		  		{
		  			flagNum1 = true;
		  		}
		  	}
		}
	  	






//下
	  	for (j = 0; j < 4; ++j)
		            		  {
		            		  	//合并
		            		  	for (i = 3; i >= 0; --i)
		            		  	{
		            		  		if (table[i][j] !=0 && i != 0)
		            		  		{
		            		  			for (z = i-1; z >= 0; --z)
		            		  			{
   		            		  				if (table[i][j] != table[z][j] && table[z][j] !=0)
		            		  				{
		            		  					break;
		            		  				}
		            		  				if (table[i][j] == table[z][j])
		            		  				{
		            		  					flagNum2 = true;
		            		  					break;
		            		  				}
		            		  			}

		            		  		}
		            		  	}

		            		  	//移动
		            		  	for (m = 3; m >= 0; --m)
		            		  	{
		            		  		if (table[m][j] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  	}

		            		  	for (k = m-1; k >= 0; --k)
		            		  	{	
		            		  		if(table[k][j] !=0 )
		            		  		{
		            		  			flagNum2 = true;
		            		  		}
		            		  	}
		            		  }
//左
		            		  for (i = 0; i < 4; ++i)
		            		  {
		            		  	//合并
		            		  	for (j = 0; j < 4; ++j)
		            		  	{
		            		  		if (table[i][j] !=0 && j != 3)
		            		  		{
		            		  			for (z = j+1; z < 4; ++z)
		            		  			{
		            		  				if (table[i][j] != table[i][z] && table[i][z] !=0)
		            		  				{
		            		  					break;
		            		  				}

		            		  				if (table[i][j] == table[i][z])
		            		  				{
		            		  					flagNum3 = true;
		            		  					break;
		            		  				}
		            		  			}

		            		  		}
		            		  	}

		            		  	//移动
		            		  	for (m = 0; m < 4; ++m)
		            		  	{
		            		  		if (table[i][m] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  	}

		            		  	for (k = m+1; k < 4; ++k)
		            		  	{	
		            		  		if(table[i][k] !=0 )
		            		  		{
		            		  			flagNum3 = true;
		            		  		}
		            		  	}
		            		  }
//右
							  for (i = 0; i < 4; ++i)
		            		  {
		            		  	//合并
		            		  	for (j = 3; j >= 0; --j)
		            		  	{
		            		  		if (table[i][j] !=0 && j != 0)
		            		  		{
		            		  			for (z = j-1; z >= 0; --z)
		            		  			{
		            		  				if (table[i][j] != table[i][z] && table[i][z] !=0)
		            		  				{
		            		  					break;
		            		  				}
		            		  				if (table[i][j] == table[i][z])
		            		  				{
		            		  					flagNum4 = true;
		            		  					break;
		            		  				}
		            		  			}
		            		  		}
		            		  	}

		            		  	//移动
		            		  	for (m = 3; m >= 0; --m)
		            		  	{
		            		  		if (table[i][m] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  	}

		            		  	for (k = m-1; k >= 0; --k)
		            		  	{	
		            		  		if(table[i][k] !=0 )
		            		  		{
		            		  			flagNum4 = true;
		            		  		}
		            		  	}
		            		  }		            		  
}


void oneMove()
{
	//每一次的游戏操作（键盘操作）

int ch;
int i,j,k,m,z;


   if( (ch=getch())!=0x1B ) /* 按 ESC 退出 */
   {
      	switch(ch)
      	{
      		case 0xE0:
      			flagNum = false;      			
        		switch(ch=getch())
         		{
            		case 72:  //上
							  for (j = 0; j < 4; ++j)
		            		  {
		            		  	//合并
		            		  	for (i = 0; i < 4; ++i)
		            		  	{
		            		  		if (table[i][j] !=0 && i != 3)//最后一个肯定没有元素可合并
		            		  		{
		            		  			for (z = i+1; z < 4; ++z)
		            		  			{
		            		  				if (table[z][j] != 0 && table[i][j] != table[z][j])
		            		  				{
		            		  					break;//肯定不能合并
		            		  				}
		            		  				if (table[i][j] == table[z][j])
		            		  				{
		            		  					table[i][j] = 2*table[i][j];
		            		  					table[z][j] = 0;
		            		  					flagNum = true;
		            		  					break;//不加就bug！！！否则z永远为4
		            		  				}
		            		  			}
		            		  		}
		            		  	}

		            		  	//移动
		            		  	int index = 0;
		            		  	for (m = 0; m < 4; ++m)
		            		  	{
		            		  		if (table[m][j] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  		index++;
		            		  	}

		            		  	for (k = m+1; k < 4; ++k)
		            		  	{	
		            		  		if(table[k][j] !=0)
		            		  		{
		            		  			table[index][j] = table[k][j];
		            		  			table[k][j] = 0;
		            		  			index++;
		            		  			flagNum = true;
		            		  		}
		            		  	}
		            		  }
            		break;
		            case 80:  //下
							  for (j = 0; j < 4; ++j)
		            		  {
		            		  	//合并
		            		  	for (i = 3; i >= 0; --i)
		            		  	{
		            		  		if (table[i][j] !=0 && i != 0)
		            		  		{
		            		  			for (z = i-1; z >= 0; --z)
		            		  			{
		            		  				if (table[i][j] != table[z][j] && table[z][j] !=0)
		            		  				{
		            		  					break;
		            		  				}
		            		  				if (table[i][j] == table[z][j])
		            		  				{
		            		  					table[i][j] = 2*table[i][j];
			            		  				table[z][j] = 0;
			            		  				flagNum = true;
		            		  					break;
		            		  				}
		            		  			}
		            		  		}
		            		  	}

		            		  	//移动
		            		  	int index = 3;
		            		  	for (m = 3; m >= 0; --m)
		            		  	{
		            		  		if (table[m][j] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  		index--;
		            		  	}

		            		  	for (k = m-1; k >= 0; --k)
		            		  	{	
		            		  		if(table[k][j] !=0 )
		            		  		{
		            		  			table[index][j] = table[k][j];
		            		  			table[k][j] = 0;
		            		  			index--;
		            		  			flagNum = true;
		            		  		}
		            		  	}
		            		  }
		            break;
		            case 75:  //左
		            		  
		            		  for (i = 0; i < 4; ++i)
		            		  {
		            		  	//合并
		            		  	for (j = 0; j < 4; ++j)
		            		  	{
		            		  		if (table[i][j] !=0 && j != 3)
		            		  		{
		            		  			for (z = j+1; z < 4; ++z)
		            		  			{
		            		  				if (table[i][j] != table[i][z] && table[i][z] !=0)
		            		  				{
		            		  					break;
		            		  				}
		            		  				if (table[i][j] == table[i][z])
		            		  				{
		            		  					table[i][j] = 2*table[i][j];
		            		  					table[i][z] = 0;
		            		  					flagNum = true;
		            		  					break;
		            		  				}
		            		  			}
		            		  		}
		            		  	}

		            		  	int index = 0;
		            		  	for (m = 0; m < 4; ++m)
		            		  	{
		            		  		if (table[i][m] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  		index++;
		            		  	}

		            		  	for (k = m+1; k < 4; ++k)
		            		  	{	
		            		  		if(table[i][k] !=0 )
		            		  		{
		            		  			table[i][index] = table[i][k];
		            		  			table[i][k] = 0;
		            		  			index++;
		            		  			flagNum = true;
		            		  		}
		            		  	}
		            		  }
		            break;
		            case 77:  //右
							  for (i = 0; i < 4; ++i)
		            		  {
		            		  	//合并
		            		  	for (j = 3; j >= 0; --j)
		            		  	{
		            		  		if (table[i][j] !=0 && j != 0)
		            		  		{
		            		  			for (z = j-1; z >= 0; --z)
		            		  			{
		            		  				if (table[i][j] != table[i][z] && table[i][z] !=0)
		            		  				{
		            		  					break;
		            		  				}
		            		  				if (table[i][j] == table[i][z])
		            		  				{
		            		  					table[i][j] = 2*table[i][j];
		            		  					table[i][z] = 0;
		            		  					flagNum = true;
		            		  					break;
		            		  				}
		            		  			}
		            		  		}
		            		  	}

		            		  	//移动
		            		  	int index = 3;
		            		  	for (m = 3; m >= 0; --m)
		            		  	{
		            		  		if (table[i][m] == 0)
		            		  		{
		            		  			break;
		            		  		}
		            		  		index--;
		            		  	}

		            		  	for (k = m-1; k >= 0; --k)
		            		  	{	
		            		  		if(table[i][k] !=0 )//&& index !=k
		            		  		{
		            		  			table[i][index] = table[i][k];
		            		  			table[i][k] = 0;
		            		  			index--;
		            		  			flagNum = true;
		            		  		}
		            		  	}
		            		  }
		            break;
		            default:break;
		         }
		         break;
		      	default:
		         break;
      }
      	displayTable();      
   }
}























