package java;
/* COP 3503C Assignment 6
This program is written by: Your Full Name */
import java.util.*;

public class Main {
    public static void main(String[] args) {
        //get the input
        Scanner input = new Scanner(System.in);

        int numStudents = input.nextInt(); //get the number of students

        //I created arrays to store the scores for each section
        int[] section1Scores = new int[numStudents + 1];
        int[] section2Scores = new int[numStudents + 1];

        //reading the scores
        for(int i = 1; i <= numStudents; i++) {
            section1Scores[i] = input.nextInt();
        }
        for(int i = 1; i <= numStudents; i++) {
            section2Scores[i] = input.nextInt();
        }

        //create this array to score the best scores for section 1 and 2
        //section 1 is maxScore[0][i]
        //section 2 is maxScore[1][i]
        long[][] maxScore = new long[2][numStudents + 1];

        long bestSection1Score = 0;
        long bestSection2Score = 0;

        //find the best possible score for each student
        for(int i = 1; i <= numStudents; i++) {
            //choose the current student from section 1 and let it extend to the best ending in section 2
            maxScore[0][i] = section1Scores[i] + Math.max(bestSection2Score, 0);
            maxScore[1][i] = section2Scores[i] + Math.max(bestSection1Score, 0); //same but vice versa

            //update the best scores seen so far
            bestSection1Score = Math.max(bestSection1Score, maxScore[0][i]);
            bestSection2Score = Math.max(bestSection2Score, maxScore[1][i]);
        }
        //print the result
        System.out.println(Math.max(bestSection1Score, bestSection2Score));
    }
}