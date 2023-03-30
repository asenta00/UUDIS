import java.util.*;
public class MyMapReduce
{
    List buckets = new ArrayList();
    List intermediateresults = new ArrayList();
    List values = new ArrayList();
	
    public void init(){
        for(int i = 1; i<=30; i++){
            values.add("ABC" + new Integer(i).toString()); //ABC1, ABC2, ... ABC30
        }
		System.out.println("**STEP 1 START**- > Running Conversion into Buckets**");
		System.out.println();
		List b = step1ConvertIntoBuckets(values,5);
		System.out.println("************STEP 1 COMPLETE*************");
		System.out.println();
		System.out.println();
		System.out.println("**STEP 2 START**- > Running **Map Function** concurrently for all Buckets");
		System.out.println();
		List res = step2RunMapFunctionForAllBuckets(b);
		System.out.println("************STEP 2 COMPLETE*************");
		System.out.println();
		System.out.println();
		System.out.println("**STEP 3 START**- > Running **Reduce Function** for collating Intermediate Results and Printing Results");
		System.out.println();
		step3RunReduceFunctionForAllBuckets(res);
		System.out.println("************STEP 3 COMPLETE*************");
    }
    
    public List step1ConvertIntoBuckets(List list,int numberofbuckets){
		int n = list.size(); // 30 vrijednosti
		int m = n / numberofbuckets; // 30 / 5 = 6
		int rem = n % numberofbuckets; // 31 % 5 = 1
		int count = 0;
		System.out.println("BUCKETS");
		for(int j = 1; j <= numberofbuckets; j++){
			List temp = new ArrayList();
			for(int i = 1; i <= m; i++){
				temp.add((String)values.get(count));
				count++;
			}
			buckets.add(temp);
			temp = new ArrayList();
		}
		if (rem != 0){
			List temp = new ArrayList();
			for(int i = 1; i <= rem; i++){
				temp.add((String)values.get(count));
				count++;
			}
			buckets.add(temp);
		}
		System.out.println();
		System.out.println(buckets);
		System.out.println();
		return buckets;
    }

    public List step2RunMapFunctionForAllBuckets(List list){
		for (int i = 0; i < list.size(); i++){
			List elementList = (ArrayList)list.get(i);
			new StartThread(elementList).run();
		}
		try {
			Thread.currentThread().sleep(2000);
		}
		catch(Exception e)
		{
		}
		return intermediateresults;
    }

    public void step3RunReduceFunctionForAllBuckets(List list){
        int sum = 0;
        for (int i = 0; i < list.size(); i++){
        // you can do some processing here, like finding max of all results etc
			int t = Integer.parseInt((String)list.get(i));
			sum += t;
		}
		System.out.println();
		System.out.println("Total Count is " + sum);
		System.out.println();
    }


    class StartThread extends Thread {
    
	
		private List tempList = new ArrayList();
        public StartThread(List list) {
            tempList = list;
		}


		public void run(){
			for (int i = 0; i < tempList.size(); i++) {
				String str = (String)tempList.get(i);
				System.out.println(str);
				synchronized(this) {
					intermediateresults.add(new Integer(str.length()).toString());
				}
			}
		}
    }
}
