import java.awt.*;
public class TestBorderLayout {

	public static void main(String[] args) {
		Frame f=new Frame("���ֹ�����");
		f.add(new Button("��һ����ť"),BorderLayout.NORTH);
		f.add(new Button("�ڶ�����ť"),BorderLayout.EAST);
		f.add(new Button("��������ť"),BorderLayout.WEST);
		f.add(new Button("���ĸ���ť"),BorderLayout.SOUTH);
		f.setSize(300,300);
		f.setVisible(true);
	}
}

