/*Write a C program that:
1.  Defines a structure containing:   Student ID (integer)
  Student Name (string - max 50 chars)   Marks (float)
  Grade (char - to be calculated by thread)
2.  Create an array of 3 student records with sample data
3.  Create 3 threads, each thread receives one student structure and:   Determines grade based on marks:
  = 85: Grade A
  = 70: Grade B
  = 60: Grade C
  = 50: Grade D
  < 50: Grade F
 Prints the student information with the calculated grade
4.  Main thread waits for all threads to complete
Answer*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
//structure for student details
struct student{
    int student_id;
    char student_name[50];
    float student_marks;
    char student_grades;   
};

void* calculate_grade(void* arg){
    struct student* s = (struct student*)arg;

    //check the grades on marks
    if (s->student_marks>=85)
        s->student_grades='A';
    else if (s->student_marks>=70)
        s->student_grades='B';
    else if (s->student_marks>=60)
        s->student_grades='C';
    else if (s->student_marks>=50)
        s->student_grades='D';
    else  
        s->student_grades='F'; 

    //print details of student
    printf("Student ID: %d\n", s->student_id);
    printf("Student Name: %s\n", s->student_name);
    printf("Student Marks: %.2f\n", s->student_marks);
    printf("Student Grades: %c\n", s->student_grades);
    return NULL;

}

int main(){
    struct student students[3]={    //array of 3 student records with sample data 
        {1,"ahmad",90,' ' },
        {2,"ahsan",75,' '},
        {3,"ali",60,' '}
    };

    pthread_t thread[3];// thread makes for three threads

    //the student information with the calculated grade
    for(int i=0;i<3;i++){
        pthread_create(&thread[i],NULL,calculate_grade,(void*)&students[i]);
    }
    //Main thread waits for all threads to complete
    for(int i=0;i<3;i++){
        pthread_join(thread[i],NULL);
    }
    return 0;

}

