# Junit_test
Junit test cases in Java using Maven build tool

How to run the project

1) Make sure you have Java (JVM/JDK) installed along with Maven.

2) Go the root folder of the project (/my-app) and run the command menitoned below

cmd: mvn test.

Expected out:

Result: Hello World!
BUILD SUCCESS!


Explanation:

1) You have a simple "" Java class which will return a value Hello World string. This is defined in the /src/test/java folder

2) A "" java class with a test case is also present in the same folder and this is written in junit test case format

3) Now since we have the code and know what technologies are involved, we have to make sure that the dependencies are mentioned in the pom.xml file. 

Dependencies added: Junit. 

Plugins added: 

build dependencies:

4) Now we just have to run the "mvn test" command from the root folder of the application(/my-app) or where the pom.xml file is present. 

5) Now maven will load the dependencies in the pom.xml file and run the test cases present in the "/src/test/java" folder (In this case we have two class file 1 with Hello world code and the other with Junit test case)

BAZINGA..!! BUILD SUCCESS..!!

Happy coding..!
