/**********************51������ʵ��************************
*  ƽ̨��Keil U4 + STC89C52RC
*  ����11.0592MHZ
******************************************************************/
/*-----------------------------------------------
  ���ƣ�ң������������������ʾ
  ���ݣ�������ң������1-9����������϶�Ӧ��ʾ����ˮ����������
------------------------------------------------*/
#include <reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#define DataPort P0   //�������ݶ˿� ����������DataPort ����P0 �滻

sbit IR = P3 ^ 2; //����ӿڱ�־
sbit LATCH1 = P2 ^ 6; //��������ʹ�ܶ˿� ������
sbit LATCH2 = P2 ^ 7; //                 λ����
sbit LCD1602 = P2 ^ 5; //�����
sbit led = P1 ^ 0; //LED��
/*------------------------------------------------
                ȫ�ֱ�������
------------------------------------------------*/

unsigned char code dofly_DuanMa[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // ��ʾ����ֵ0~9
unsigned char led_Order[10] = {0xff, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0x00};//LED
unsigned char irtime; //������ȫ�ֱ���
unsigned int order1;//dofly_duanma_order

bit irpro_ok, irok;
unsigned char IRcord[4];//�����źŵ�4���ֽ�
unsigned char irdata[33];//���յ���33λ

/*------------------------------------------------
                  ��������
------------------------------------------------*/

void Ir_work(void);//����ܺ�LED
void Ircordpro(void);//����ң�ؽ���
/*------------------------------------------------
                ��ʱ��0��ʼ��
------------------------------------------------*/
void TIM0init(void) //��ʱ��0��ʼ��
{
    TMOD = 0x02; //��ʱ��0������ʽ2��TH0����װֵ��TL0�ǳ�ֵ
    TH0 = 0x00;  //����ֵ
    TL0 = 0x00;  //��ʼ��ֵ
    ET0 = 1;     //���ж�
    TR0 = 1;
}
/*------------------------------------------------
                  �ⲿ�ж�0��ʼ��
------------------------------------------------*/
void EX0init(void)
{
    IT0 = 1; //ָ���ⲿ�ж�0�½��ش�����INT0 (P3.2)
    EX0 = 1; //ʹ���ⲿ�ж�
    EA = 1;  //�����ж�
}

/*------------------------------------------------
                  ��ʱ��0�жϴ���
------------------------------------------------*/

void tim0_isr(void) interrupt 1 using 1
{
    irtime++; //���ڼ���2���½���֮���ʱ��
}

/*------------------------------------------------
                  �ⲿ�ж�0�жϴ���
------------------------------------------------*/
void EX0_ISR(void) interrupt 0 //�ⲿ�ж�0������
{
    static unsigned char i; //���պ����źŴ���
    static bit startflag;   //�Ƿ�ʼ�����־λ

    if (startflag)
    {
        if (irtime < 63 && irtime >= 33) //������ TC9012��ͷ�룬9ms+4.5ms
            i = 0;
        irdata[i] = irtime; //�洢ÿ����ƽ�ĳ���ʱ�䣬�����Ժ��ж���0����1
        irtime = 0;
        i++;
        if (i == 33)
        {
            irok = 1;
            i = 0;
        }
    }
    else
    {
        irtime = 0;
        startflag = 1;
    }
}

/*------------------------------------------------
                  ��ֵ����
------------------------------------------------*/

void Ir_work(void) //�����ֵɢת����
{
    switch (IRcord[2]) //�жϵ���������ֵ
    {
    case 0x16:
        DataPort = dofly_DuanMa[0];
		order1 = 0;
        P1 = led_Order[0];
        break; //0
    case 0x0c:
        DataPort = dofly_DuanMa[1];
		order1 = 1;
        P1 = led_Order[1];
        break; //1 ��ʾ��Ӧ�İ���ֵ
    case 0x18:
        DataPort = dofly_DuanMa[2];
		order1 = 2;
        P1 = led_Order[2];
        break; //2
    case 0x5e:
        DataPort = dofly_DuanMa[3];
		order1 = 3;
        P1 = led_Order[3];
        break; //3
    case 0x08:
        DataPort = dofly_DuanMa[4];
		order1 = 4;
        P1 = led_Order[4];
        break; //4
    case 0x1c:
        DataPort = dofly_DuanMa[5];
		order1 = 5;
        P1 = led_Order[5];
        break; //5
    case 0x5a:
        DataPort = dofly_DuanMa[6];
		order1 = 6;
        P1 = led_Order[6];
        break; //6
    case 0x42:
        DataPort = dofly_DuanMa[7];
		order1 = 7;
        P1 = led_Order[7];
        break; //7
    case 0x52:
        DataPort = dofly_DuanMa[8];
		order1 = 8;
        P1 = led_Order[8];
        break; //8
    case 0x4a:
        DataPort = dofly_DuanMa[9];
		order1 = 9;
        P1 = led_Order[9];
        break; //9
	case 0x07:
		order1 = order1==0?9:order1-1;
		DataPort = dofly_DuanMa[order1];
		P1 = led_Order[order1];
		break;
	case 0x15:
		order1 = order1==9?0:order1+1;
		DataPort = dofly_DuanMa[order1];
		P1 = led_Order[order1];
		break;
    default:
        break;
    }

    irpro_ok = 0; //������ɱ�־
}
/*------------------------------------------------
                ������ֵ����
------------------------------------------------*/
void Ircordpro(void) //������ֵ������
{
    unsigned char i, j, k;
    unsigned char cord, value;

    k = 1;
    for (i = 0; i < 4; i++) //����4���ֽ�
    {
        for (j = 1; j <= 8; j++) //����1���ֽ�8λ
        {
            cord = irdata[k];
            if (cord > 7) //����ĳֵΪ1������;����о��Թ�ϵ������ʹ��12M���㣬��ֵ������һ�����
                value |= 0x80;
            if (j < 8)
            {
                value >>= 1;
            }
            k++;
        }
        IRcord[i] = value;
        value = 0;
    }
    irpro_ok = 1; //������ϱ�־λ��1
}

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main(void)
{
    EX0init();  //��ʼ���ⲿ�ж�
    TIM0init(); //��ʼ����ʱ��
    LCD1602 = 0;
    DataPort = 0x3e; //ȡλ�� ��һλ�����ѡͨ����������0011 1110
    LATCH2 = 1;      //λ����
    LATCH2 = 0;

    while (1) //��ѭ��
    {
	LATCH1=0;
	LATCH2=0;

	P0=0x4f;	   //���֡�3���Ĵ���
	LATCH1=1;
	LATCH2=0;

	P0=0xfe;	   //ѡ�е�һ�������
	LATCH1=1;
	LATCH2=0;
	/*
        if (irok) //������պ��˽��к��⴦��
        {
            Ircordpro();
            irok = 0;
        }
		
        if (irpro_ok) //�������ú���й��������簴��Ӧ�İ�������ʾ��Ӧ�����ֵ�
        {
            Ir_work();
        }
		*/
    }
}
