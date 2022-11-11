#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> /* for ENOSYS */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int matrix_allocate(matrix_t *m, int rows, int columns)
{
    /* implement the function here ... */
    // m = (matrix_t *)malloc(sizeof(matrix_t));

    if (m == NULL)
    {
        return -1;
    }

    m->rows = rows;
    m->columns = columns;
    m->content = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++)
    {
        m->content[i] = (int *)malloc(sizeof(int) * columns);
    }

    if (m->content == NULL)
    {
        return -1;
    }

    return 0; /* ENOSYS is a  standard error code that means 'function
                       not implemented'. We use it to force the failure of tests
                       while the functions are not written. Make sure to remove
                       it when you start to work on a function */
}

void matrix_free(matrix_t *m)
{
    /* implement the function here ... */
    for (int i = 0; i < m->rows; i++)
    {
        free(m->content[i]);
    }
    free(m->content);
    // free(m);
}

void matrix_init_zeros(matrix_t *m)
{
    /* implement the function here ... */
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            m->content[i][j] = 0;
        }
    }
}

int matrix_init_identity(matrix_t *m)
{
    /* implement the function here ... */
    if (m->rows != m->columns)
    {
        return -1;
    }
    else if (m->rows <= 0)
    {
        return -1;
    }

    else
    {
        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                if (i == j)
                {
                    m->content[i][j] = 1;
                }
                else
                {
                    m->content[i][j] = 0;
                }
            }
        }
        return 0;
    }
}
void matrix_init_rand(matrix_t *m)
{
    /* implement the function here ... */
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            m->content[i][j] = rand() % 201 - 100; // 0...200 - 100
        }
    }
}

int matrix_equal(matrix_t *m1, matrix_t *m2)
{
    /* implement the function here ... */
    if (m1->rows != m2->rows)
    {
        return 0;
    }
    else if (m1->columns != m2->columns)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < m1->rows; i++)
        {
            for (int j = 0; j < m1->columns; j++)
            {
                if (m1->content[i][j] != m2->content[i][j])
                {
                    return 0;
                }
            }
        }
        return 1;
    }
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result)
{
    /* implement the function here ... */
    if (m1->rows != m2->rows)
    {
        return -1;
    }
    else if (m1->columns != m2->columns)
    {
        return -1;
    }
    else
    {
        int allocResult = matrix_allocate(result, m1->rows, m1->columns);
        if (allocResult == -1)
        {
            return -1;
        }
        else
        {
            for (int i = 0; i < m1->rows; i++)
            {
                for (int j = 0; j < m1->columns; j++)
                {
                    result->content[i][j] = m1->content[i][j] + m2->content[i][j];
                }
            }
            return 0;
        }
    }
}

int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result)
{
    /* implement the function here ... */
    int allocResult = matrix_allocate(result, m->rows, m->columns);
    if (allocResult == -1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                result->content[i][j] = m->content[i][j] * scalar;
            }
        }
        return 0;
    }
}

int matrix_transposition(matrix_t *m, matrix_t *result)
{
    /* implement the function here ... */
    int allocResult = matrix_allocate(result, m->columns, m->rows);

    if (allocResult == -1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < m->rows; i++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                result->content[j][i] = m->content[i][j];
            }
        }
        return 0;
    }
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result)
{
    /* implement the function here ... */
    if (m1->columns != m2->rows)
    {
        return -1;
    }
    else
    {
        int allocResult = matrix_allocate(result, m1->rows, m2->columns);
        if (allocResult == -1)
        {
            return -1;
        }
        else
        {
            for (int i = 0; i < m1->rows; i++)
            {
                for (int j = 0; j < m2->columns; j++)
                {
                    result->content[i][j] = 0;
                    for (int k = 0; k < m1->columns; k++)
                    {
                        result->content[i][j] += m1->content[i][k] * m2->content[k][j];
                    }
                }
            }
            return 0;
        }
    }
}

int matrix_dump_file(matrix_t *m, char *output_file)
{
    /* implement the function here ... */ // 이거는 파일 저장하는 거임
    if (m == NULL)
    {
        return -1;
    }
    else
    {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC);
        if (fd == -1)
        {
            return -1;
        }
        int rows = m->rows;
        int columns = m->columns;
        char space = ' ';
        char newline = '\n';
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                write(fd, &m->content[i][j], sizeof(int));
                if (j != columns - 1)
                {
                    write(fd, &space, sizeof(char));
                }
            }
            if (i != rows - 1)
            {
                write(fd, &newline, sizeof(char));
            }
        }
        close(fd);
    }
    return 0;
}

int matrix_allocate_and_init_file(matrix_t *m, char *input_file)
{
    /* implement the function here ... */
    FILE *fd = fopen(input_file, "r");
    if (fd == NULL)
    {
        return -1;
    }

    int allocResult = matrix_allocate(m, m->columns, m->rows);

    if (allocResult == -1)
    {
        return -1;
    }
    else
    {
        int rows = m->rows;
        int columns = m->columns;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (j != columns - 1)
                {
                    fscanf(fd, "%d ", &m->content[i][j]);
                }
                else
                {
                    if (i != rows - 1)
                    {
                        fscanf(fd, "%d\n", &m->content[i][j]);
                    }
                    else
                    {
                        fscanf(fd, "%d", &m->content[i][j]);
                    }
                }
            }
        }
        fclose(fd);
    }
    return 0;
}

// int main(void)
// {
//     matrix_t m;
//     int re = matrix_allocate(&m, 3, 3);
//     printf("%d", re);
//     // matrix_init_identity(m);
//     matrix_free(&m);
//     return 0;
// }