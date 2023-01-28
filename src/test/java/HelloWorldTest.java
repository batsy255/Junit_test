import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class HelloWorldTest {

  @Test
  public void testSayHello() {
    HelloWorld hw = new HelloWorld();
    String result = hw.sayHello();
    System.out.println("RESULT: " + result);
    assertEquals("Hello World", result);
  }
}
