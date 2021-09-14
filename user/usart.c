#include "usart.h"
/*
USART1_TX--PA9 ; USART1_RX--PA10
USART2_TX--PA2 ; USART2_RX--PA3
USART3_TX--PB10 ; USART3_RX--PB11
*/

u8 USART_RX_BUF[200];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���
int  distance;

//	printf("distance = %d mm \r\n",distance );

void USART1_INIT(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_USART1 ,ENABLE );
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
 	// ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 ;
    GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE ;
	NVIC_Init(&NVIC_InitStructure); 
	
    USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode =USART_Mode_Rx |USART_Mode_Tx ;
	USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
    USART_InitStructure.USART_WordLength =USART_WordLength_8b;
    USART_Init(USART1 ,&USART_InitStructure);
	
	USART_ITConfig(USART1 ,USART_IT_RXNE ,DISABLE ); 
    USART_Cmd(USART1 ,ENABLE ); 	
 	
}
void USART2_INIT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  ,ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 ,ENABLE );
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
 	// ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 ;
    GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE ;
	NVIC_Init(&NVIC_InitStructure); 
	
    USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode =USART_Mode_Rx |USART_Mode_Tx ;
	USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
    USART_InitStructure.USART_WordLength =USART_WordLength_8b;
    USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE ,ENABLE  ); 
    USART_Cmd(USART2,ENABLE ); 	
	
}

void USART3_INIT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE );
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_InitStructure);
 	// ��USART Rx��GPIO����Ϊ��������ģʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11 ;
    GPIO_Init(GPIOB ,&GPIO_InitStructure);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
    USART_InitStructure.USART_Mode =USART_Mode_Rx |USART_Mode_Tx ;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
    USART_InitStructure.USART_WordLength =USART_WordLength_8b;
    USART_Init(USART3 ,&USART_InitStructure);
    USART_Cmd(USART3 ,ENABLE ); 	
	
}
//Send 8Bits(1B)

//Send 8Bits_Array

//Send Strings


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(THE_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(THE_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(THE_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(THE_USARTx);
}
//�жϽ���
void USART1_IRQHandler(void)                	
	{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(200))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
} 

void USART2_IRQHandler(void)
{
	static u8 res,cnt=0;
	if(USART_GetITStatus(USART2 ,USART_IT_RXNE )!=RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE ); 
		res = USART_ReceiveData(USART2);
		if(res==0x5A&&cnt==0)
		{
			cnt=1;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
		}
		else if(res==0x5A&&cnt==1)
		{
			cnt =2;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
		}
		else if(res==0x15&&cnt==2)
		{
			cnt =3;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
		} 	
		else if(res==0x03&&cnt==3)
		{
			cnt=4;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
	    } 
		else if(cnt==4)
		{
			distance =res;
			cnt=5;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
		}
		  else  if(cnt==5)
		{
			distance =distance<<8 |res ;
			cnt=0;
			//printf("res = %x ,  cnt = %d \r\n",res,cnt  ) ;
		}
	   
	}
}


/*
    u8  t;
    u8  len;
if(USART_RX_STA&0x8000) //�������
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
				for(t=0;t<len;t++)
				{
					printf("usart_rx_buf[%d]=%c \r\n ",t,USART_RX_BUF[t]) ;
				}
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
			
		}
*/




