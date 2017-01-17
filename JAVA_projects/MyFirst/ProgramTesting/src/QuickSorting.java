import java.util.ArrayList;

public class QuickSorting extends Sort{
	
	
	private ArrayList<Integer> _list;
	QuickSorting(ArrayList<Integer> list){
		this._list = list;
	}

	@Override
	public void dumplist() {
		// TODO Auto-generated method stub
		System.out.println(this._list);
		
	}

	@Override
	public void sayhi() {
		// TODO Auto-generated method stub
		System.out.println("hello QuickSort");
		
	}
	
	
	
	public void test()
	{
		int high_bound = 0;
		int low_bound = this._list.size()-1;
		int new_pivot_pos = partition(this._list,high_bound,low_bound, 0,"ROOT");
		
			
	}
	
	private int partition(ArrayList<Integer> list,int begin_pos,int end_pos,int count,String arg)
	{
		Integer pivot;
		int s_begin = begin_pos;
		int s_end = end_pos;
		
		
		if(begin_pos >= end_pos){
			return 0;
		}
		
		//if (count >100) return -1;
		
		pivot = list.get(begin_pos);
		while(begin_pos<end_pos)
		{
			while(end_pos > begin_pos && list.get(end_pos) >= pivot ) 
			{
				end_pos--;
			}
			list.set(begin_pos, list.get(end_pos));
			while(end_pos > begin_pos && list.get(begin_pos)<= pivot){
				begin_pos ++;
			}
			list.set(end_pos, list.get(begin_pos));
		}
		list.set(begin_pos, pivot);
		
		
		partition(list, s_begin, begin_pos-1,count+1,"LEFT");
		partition(list, begin_pos+1,s_end, count+1,"RIGHT"); //must be begin_pos+1, in case of the first element is the least value of this array
		return begin_pos;
		
	}

}
