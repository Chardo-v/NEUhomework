class TestInteger
{
	public static void main(String[] args)
	{
		int w = Integer.parseInt(args[0]);  //��һ�ַ���
		int h = new  Integer(args[1]).intValue(); //�ڶ��ַ���
		//int h = Integer.valueOf(args[1]).intValue(); //�����ַ���
		for(int i=0;i<h;i++)
		{
		StringBuffer sb=new StringBuffer();
		for(int j=0 ;j<w;j++)
		{
			sb.append('*');
		}
		System.out.println(sb.toString());
		}
	}
}