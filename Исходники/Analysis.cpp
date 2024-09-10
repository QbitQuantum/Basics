double average_analysis(const Vec<Student_info>& students)
{
    Vec<double> grades;

    transform(students.begin(), students.end(),
              back_inserter(grades), average_grade);
    return median(grades);
}