import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;
import weka.classifiers.Evaluation;
import weka.classifiers.bayes.NaiveBayes;
import weka.core.Instances;

public class NBayes {
	
	public static void main(String[] args) throws Exception {
		
		BufferedReader read = new BufferedReader (new FileReader("src/test.arff")); 
	    Instances train = new Instances(read); 
	    train.setClassIndex(train.numAttributes()-1);
		
		NaiveBayes nB = new NaiveBayes();
		nB.buildClassifier(train);
		Evaluation eval = new Evaluation(train);
		eval.crossValidateModel(nB, train, 10, new Random(1));

		System.out.println("Naive Bayes Classification\n");
		System.out.println(eval.toSummaryString("\nResults===============>\n",true));
		//System.out.println(eval.fMeasure(1)+" "+eval.precision(1)+" "+eval.recall(1));
		System.out.println(eval.toMatrixString("\nConfusion Matrix: false positives and false negatives\n======\n"));
		System.out.println(eval.toClassDetailsString("Class Details..\n"));
		//System.out.println(eval.truePositiveRate(1));
	
	}
}