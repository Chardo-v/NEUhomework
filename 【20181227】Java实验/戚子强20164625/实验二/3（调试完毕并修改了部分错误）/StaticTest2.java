class StaticTest2
{ 
  int age;
  boolean sex;
  String name;
  static long population;		//��̬����
  
  static void printPopulation(){}	//��̬����
  
  static void print()
  {   
   System.out.println(population);
   System.out.println(age);
  }
  
  public static void main(String[] as)
  {
    //StaticTest2 man = new StaticTest2();
    //man.population = 100;
    //System.out.println(StaticTest2.population);   //100
    //man.print();
    System.out.println(age);
    StaticTest2.print();
    print();
  }
}
