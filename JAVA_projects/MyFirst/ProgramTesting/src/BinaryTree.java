import java.util.ArrayList;

public class BinaryTree {
	
	private class TreeNode
	{
		private int val;
		private TreeNode left = null, right = null;
		
		TreeNode(int val)
		{
			this.val = val;
		}
		
		public int getValue()
		{
			return this.val;
		}
		
		public void setValue(int val)
		{
			this.val = val;
		}
		public void setLeft(TreeNode left)
		{
			this.left = left;
		}
		public void setRight(TreeNode right)
		{
			this.right = right;
		}
		public TreeNode getLeft(){
			return this.left;
		}
		public TreeNode getRight(){
			return this.right;
		}
	}
	
	private TreeNode root = new TreeNode(0);
	
	public void createBT()
	{
		this.root.setValue(101);
		this.root.setLeft(new TreeNode(15));
		this.root.setRight(new TreeNode(95));
		this.root.getLeft().setLeft(new TreeNode(54));
		this.root.getLeft().setRight(new TreeNode(4));
		this.root.getRight().setRight(new TreeNode(41));
	
	}
	public void preorder(){
		ArrayList<Integer> values  = new ArrayList<Integer>();
		preorderquery(this.root, values);
		System.out.println(values);
		
		
	}
	private TreeNode preorderquery(TreeNode node, ArrayList<Integer> values){
		
		if (node == null) return null;
		
		values.add(node.getValue());
		
		preorderquery(node.getLeft(), values);
		preorderquery(node.getRight(), values);
		
		
		return node;
	}

}
