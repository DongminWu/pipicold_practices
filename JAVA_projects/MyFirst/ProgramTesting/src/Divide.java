
public class Divide {
	public static int div(int a, int b) throws ArithmeticException{
		if (b == 0)
		{
			throw new ArithmeticException("Cannot be Zero");
		}
		return a/b;
		
	}

}
