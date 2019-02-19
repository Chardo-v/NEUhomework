class MyKey
{
	private String name;
	private int age;
	public MyKey(String name,int age)
	{
		this.name = name;
		this.age = age;
	}
	public String toString()
	{
		return new String(name + "," + age);
	}
	public boolean equals(Object obj)
	{
		if(obj instanceof MyKey)
		{
			MyKey objTemp = (MyKey)obj;
			if(name.equals(objTemp.name) && age==objTemp.age)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//����obj����MyKey���ʵ���������Ͳ������뵱ǰ���������
		else 
		{
			return false;
		}
	}
	public int hashCode()
	{
		return name.hashCode() + age;
	}
}