import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.SparkContext_
/**
  * Created by vamshirajarikam on 10/2/16.
  */
object InvertedIndex{
  def main(args: Array[String]) {

    val sparkConf = new SparkConf().setAppName("InvertedIndex").setMaster("local[*]")
    //val sc=new SparkContext("local","Inverted Index")
    val sc=new SparkContext(sparkConf)
    val input = sc.textFile("/Users/vamshirajarikam/Downloads/SparkTransformationActions/src/main/scala/UMKC.csv")
    val index= input.map{line => val array = line.split("\t",2)(array(0),array(1))}
      .flatMap{case(path, text) => text.split(" ") }
      .map{case (w,p) => ((w,p),1)}
      .reduceByKey{
        case (n1,n2) => n1 + n2
      }
      .map{
        case ((w,p),n) => (w,(p,n))
      }
      .groupBy{
        case (w,(p,n)) => w
      }
      .map{
        case (w,seq) =>
          val seq2 =seq map {
            case (_, (p,n))=>(p,n)
          }
          (w, seq2.mkString(","))
      }
    index.saveAsTextFile("output")
    sc.stop()
  }
}

