import java.util.*;

/**
 * 
 */

/**
 * @author dong
 *
 */
public class ProgramTesting {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("hello pipicold!");
		Sort A = new PopSort();
		A.sayhi();
		
		ArrayList<Integer> testlist = new ArrayList();
		testlist.add(9);
		testlist.add(1);
		testlist.add(3);
		testlist.add(6);
		testlist.add(2);
		testlist.add(4);
		testlist.add(7);
		testlist.add(8);
		testlist.add(12);
		testlist.add(123);
		testlist.add(13);
		testlist.add(0);
		testlist.add(5);
		
		QuickSorting QS = new QuickSorting(testlist);
		QS.dumplist();
		QS.test();
		QS.dumplist();
		
		BinaryTree BT = new BinaryTree();
		BT.createBT();
		BT.preorder();
		
		
		TestingPlatformA B = new TestingPlatformA();
		System.out.println("HTTP 1.1 "+B.responseCode());
		System.out.println("METHOD: "+B.responseMethod());
		
		System.out.println(""+Divide.div(9, 3));

	}

}

