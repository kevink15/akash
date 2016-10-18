import java.io.BufferedReader;
import java.io.FileReader;
import weka.classifiers.Evaluation;
import weka.classifiers.trees.J48;
import weka.core.Instances;

public class DecisionTree { 
	
    public static void main (String[] args) throws Exception 
    { 
        BufferedReader breader = new BufferedReader (new FileReader("src/test.arff")); 
        Instances train = new Instances(breader); 
        train.setClassIndex(train.numAttributes()-1); 
        
        breader = new BufferedReader (new FileReader("src/test.arff")); 
        Instances test = new Instances(breader); 
        test.setClassIndex(test.numAttributes()-1); 
        
        breader.close();
      
        J48 tree= new J48(); 
        tree.setOptions(null); 
        tree.buildClassifier(train); 
       // Instances labeled = new Instances (test); 
         
        Evaluation eval = new Evaluation(train);
		eval.evaluateModel(tree, test);
		System.out.println("Decision Tree\n");
		System.out.print(eval.toSummaryString("\nSummary\n======\n", false));
		System.out.print(eval.toClassDetailsString("\nClass Details\n======\n"));
		System.out.print(eval.toMatrixString("\nConfusion Matrix: false positives and false negatives\n======\n"));
	//	System.out.println("Fmeasure"+eval.fMeasure(1));
    			        
    } 
} 