#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_STR_LEN 100
#define TEST_NUM 5
#define BOARD_X 6
#define BOARD_Y 6

void string(char *buf)
{
        int len = strlen(buf);
        int i = 0;
        int j;
        while (i < len / 2) {
                j = len - i - 1;
                buf[i] ^= buf[j];
                buf[j] ^= buf[i];
                buf[i] ^= buf[j];
                i++;
        }
}

void rec_two(unsigned int dec_num, char *bin_buf)
{
        if (dec_num % 2)
                strcat(bin_buf, "1");
        else
                strcat(bin_buf, "0");

        if (dec_num <= 1) {
                string(bin_buf);
                return;
        }

        rec_two(dec_num / 2, bin_buf);
}


long rec_pow(int b, unsigned int p)
{
        if (p <= 0)
                return 1;

        return b * rec_pow(b, --p);
}


long rec_pow_parity(long b, unsigned int p)
{
        if (p <= 0)
                return 1;

        if (p % 2)
                return b * rec_pow_parity(b, --p);
        else
                return rec_pow_parity(b * b, p / 2);
}


int king_routes(int x, int y, int board[][BOARD_Y])
{
        if (board[x][y])
                return 0;
        else if (x == 0 && y == 0)
                return 0;
        else if (x == 0 || y == 0)
                return 1;
        else
                return king_routes(x - 1, y, board) + king_routes(x, y - 1, board);
}

int main()
{
        setlocale(LC_ALL, "Rus");
        char bin_buf[MAX_STR_LEN];
        unsigned int test_num1 = 110;
        unsigned int test_num2 = 255;

        printf("Задание 1: Перевод числа из десятичной в бинарную систему\n");

        bin_buf[0] = '\0';
        rec_two(test_num1, bin_buf);
        printf("%u in binary is %s\n", test_num1, bin_buf);

        bin_buf[0] = '\0';
        rec_two(test_num2, bin_buf);
        printf("%u В бинарном представлении: %s\n", test_num2, bin_buf);


        int test_bases[TEST_NUM] = {2, -7};
        unsigned int test_pows[TEST_NUM] = {5, 16};
        long result;

        printf("\n2.1: Задание:2.1:  Возведение числа a в степень b\n");

        for (int i = 0; i < TEST_NUM; i++) {
                for (int j = 0; j < TEST_NUM; j++) {
                        result = rec_pow(test_bases[i], test_pows[j]);
                        printf("%d число возведено %u is %ld\n",
                               test_bases[i],
                               test_pows[j],
                               result);
                }
        }


        printf("\nЗадание: 2.2   Возведение числа a в степень с четностью степени:\n");

        for (int i = 0; i < TEST_NUM; i++) {
                for (int j = 0; j < TEST_NUM; j++) {
                        result = rec_pow_parity(test_bases[i], test_pows[j]);
                        printf("%d Число возведено %u is %ld\n",
                               test_bases[i],
                               test_pows[j],
                               result);
                }
        }


        int board[BOARD_X][BOARD_Y];

        for (int i = 0; i < BOARD_Y; i++) {
                for (int j = 0; j < BOARD_X; j++) {
                        board[i][j] = 0;
                }
        }

        printf("\n3: Задание 3: нахождение количества маршрутов шахматного короля с препятствиями [%d,%d]\n",
               BOARD_X, BOARD_Y);


        board[1][1] = 1;
        board[2][3] = 1;

        for (int y = 0; y < BOARD_Y; y++) {
                for (int x = 0; x < BOARD_X; x++) {
                        printf("%3d", king_routes(x, y, board));
                }
                printf("\n");
        }
}
