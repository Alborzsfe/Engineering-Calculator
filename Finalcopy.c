#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_HISTORY 100
#define pi 3.14159265359
#define e 2.71828
#define WIDTH 90   // عرض نمودار
#define HEIGHT 25  // ارتفاع نمودار
#define TICKS 7    // تعداد تقسیمات هر محور (تعداد تقسیمات جدید برای تنظیم دقیق)

// منو ها اینجاس
void clear_screen();
void display_logo();
void user_interface();
void display_menu();
void plot_function_ascii(const char *function);
void view_history(char history[][256], int history_count, double res[]);
void mathematical_expression();
void plot_function();



// محاسباتی های اینجاس
#define MAX_EXPR_LEN 100
double evaluateSimpleExpression(const char *expression);
double applyOperator(double a, double b, char op);
double calculateExpression(const char *expression);
int isOperator(char c);
int precedence(char op);
double fact(double x);
void removeSpaces(char *str);
double ANS(int);
void replacePiWithPiValue(char *str);
void make_manfi_dar_manfi_to_mosbat(char *str);
void replace_E_With_neper_Value(char *str);

// نموداری ها
void replace_x_with_number(char* str, double num);
void draw_plot(double x_min, double x_max, double x_values[], double y_min, double y_max, double y_values[], int count,char input[] );
void findMinMax(double arr[], int size, double *min, double *max);

// سیو ها
void save_to_history(const char *filename, const char *history, double res);
int load_history(const char *filename, char history[MAX_HISTORY][256], double res[MAX_HISTORY]);
void clear_history(const char *filename);

// گلوبال ها
double res[MAX_HISTORY];
int history_count = 0;
char history[MAX_HISTORY][256];
int radin1_or_degree2 = 1 ;
int run_mathematical = 1;
int run_plot = 1;
const char *filename = "calculator_history.txt";

int main() {
    system("chcp 65001 > nul");
    user_interface();
    return 0;
}

void user_interface() {
    int choice;
    
    while (1) {
        int history_count = load_history(filename,history,res);
        clear_screen();
        display_logo();  // نمایش لوگوی برنامه
        display_menu();  // نمایش منوی اصلی
        scanf("%d", &choice);
        getchar();  // حذف کاراکتر newline از بافر ورودی

        switch (choice) {
            case 1:
                mathematical_expression();
                break;
            case 2:
                plot_function();
                break;
                
            case 3:
                view_history(history, history_count, res);
                break;

            case 4:
                clear_screen();
                printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                printf("║                                                👋 Goodbye                                                ║\n");
                printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
                printf("\n🔹 Exiting the program. Have a great day!\n");
                exit(0);

            default:
                printf("\n❌ Invalid option. Please try again.\n");
                printf("\n🔹 Press Enter to return to the main menu...\n");
                getchar();
        }
    }

}

void display_logo() {
    printf("\n");
    printf("        ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗███████╗██████╗ ██╗███╗   ██╗ ██████╗ \n");
    printf("        ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝██╔════╝██╔══██╗██║████╗  ██║██╔════╝ \n");
    printf("        █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  █████╗  ██████╔╝██║██╔██╗ ██║██║  ███╗\n");
    printf("        ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  ██╔══╝  ██╔══██╗██║██║╚██╗██║██║   ██║\n");
    printf("        ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗███████╗██║  ██║██║██║ ╚████║╚██████╔\n");
    printf("        ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ \n");
    printf("                   ██████╗ █████╗ ██╗      ██████╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗    \n");
    printf("                  ██╔════╝██╔══██╗██║     ██╔════╝██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗   \n");
    printf("                  ██║     ███████║██║     ██║     ██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝   \n");
    printf("                  ██║     ██╔══██║██║     ██║     ██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗   \n");
    printf("                  ╚██████╗██║  ██║███████╗╚██████╗╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║  \n");
    printf("                   ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝ \n");
    printf("\n");
}

void display_menu() {
    printf("\n┌─────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                              Main Menu                                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│ 1  Enter a mathematical expression                                                                      │\n");
    printf("│ 2  Plot a function                                                                                      │\n");
    printf("│ 3  View history                                                                                         │\n");
    printf("│ 4  Exit                                                                                                 │\n");
    printf("└─────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n🔹 Choose an option: ");
}

void mathematical_expression(){
        clear_screen();
                printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
                printf("║                                                 ✏ Expression                                             ║\n");
                printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
                //printf("if you want work with radian enter 1 else for working with degree enter 2 ");
                //scanf("%d",&radin1_or_degree2);
                //getchar();
                printf("\n🔹 Enter your mode (1 radian - 2 degree): ");
                scanf("%d",&radin1_or_degree2);
                run_mathematical = 1;
    while (run_mathematical == 1)
    {
        char input[256] ,input_copy[256] ;

                getchar();
                printf("\n🔹 Enter your expression: ");
                fgets(input, sizeof(input), stdin);
                //input[strcspn(input, "\n")] = '\0';

                removeSpaces(input);

                strlwr(input);
                strcpy(input_copy, input);

                replacePiWithPiValue(input_copy);
                make_manfi_dar_manfi_to_mosbat(input_copy);
                replace_E_With_neper_Value(input_copy);

                double result = calculateExpression(input_copy);
                save_to_history(filename, input, result);
                int history_count = load_history(filename,history,res);
                //  if (history_count < MAX_HISTORY) {
                //     strcpy(history[history_count], input);
                //     res[history_count++] = result ;
                //  }


                printf("\n🔎 %d. Processing :",history_count);

                printf("\033[1;33m"); 
                printf("  %s\n",input);
                printf("\033[0m");

                printf("🧮 Result:   🟰");
                printf("\033[1;33m");
                printf("    %lf\n", result);
                printf("\033[0m");
                printf("\n🔹 Press 1 to process the new phrase and 2 to go to the main menu...  ");
                scanf("%d",&run_mathematical);
                printf("\n══════════════════════════════════════════════════════════════════════════════════════════════════════════\n");
                // getchar();
    }
}

void view_history(char history[][256], int history_count, double res[]) {
    clear_screen();
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                   🕒 History                                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    // if (history_count == 0) {
    //     printf("\nNo calculation history available.\n");
    //     getchar();
    //     return;
    // }

    for (int i = 0; i < history_count; i++) {
        printf(" %d. %s \t\t\t\n  \t\t\t\t\t\t🟰    %f \n", i + 1, history[i] , res[i]);
    }
    
    printf("\n🔹 Press 1 -> to delete & 0 -> to return main menu :    ");
    int del_or_not_history ;
    scanf("%d",&del_or_not_history);
    if (del_or_not_history == 0)
    {
        /*nothing hapend */
    }
    else if (del_or_not_history == 1)
    {
        clear_history(filename);
        getchar();
    }
    else{
        printf("what u mean?😒");
        getchar();
        
    }
    
    
    getchar();
}

void plot_function() {
    char navigation;
    char input[256] ,  input_copy[256] , input_copy_copy[256];
    double x_min, x_max, y_min=-10 , y_max=10, y_values[100], x_values[100] ;
    clear_screen();
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                                  📈 Plotting                                             ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("\n🔹 Enter your mode (1 radian - 2 degree): ");
        scanf("%d", &radin1_or_degree2);

        // پاک کردن بافر پس از خواندن ورودی عددی
        while (getchar() != '\n');

        printf("\n🔹 Enter the function to plot (sin(x), x^2 , ...): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // حذف newline در انتهای رشته
        strlwr(input);

        printf("\n🔹 Enter the Domain : ");
        scanf("%lf %lf", &x_min, &x_max);
        getchar(); // پاک کردن newline باقی‌مانده در بافر
        printf("\n🔹 Enter the Range function (prefer -10 to 10) or (0 0 when you dont know about range) : ");
        scanf("%lf %lf", &y_min, &y_max);
        getchar(); // پاک کردن newline باقی‌مانده در بافر
        strcpy(input_copy, input);

        replacePiWithPiValue(input_copy);
        replace_E_With_neper_Value(input_copy);
        make_manfi_dar_manfi_to_mosbat(input_copy);

        
        double x_min_copy = x_min, x_max_copy=  x_max, y_min_copy = y_min , y_max_copy = y_max;

    run_plot = 1;
    while (run_plot == 1)
    {
        clear_screen();
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║                                                  📈 Plotting                                             ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("\n🎨 Drawing an ASCII plot for: ");

        printf("\033[1;32m");
        printf("%s\n", input);
        printf("\033[0m");



        for (int i = 0; i < 100; i++) {
            x_values[i] = x_min + i * ((x_max - x_min) / 99.0); // 100 مقدار از x_min تا x_max
            double num = x_values[i];
            strcpy(input_copy_copy, input_copy);
            replace_x_with_number(input_copy_copy, num);
            make_manfi_dar_manfi_to_mosbat(input_copy_copy);
            
            y_values[i] = calculateExpression(input_copy_copy);
        }
        
        if (y_min == 0 && y_max == 0 )
        {
            findMinMax(y_values ,100, &y_min, &y_max);
        }
        
        
        
        draw_plot(x_min, x_max, x_values, y_min, y_max, y_values, 100, input);

        printf("\n🔹 Press 'W' 'A' 'S' 'D' to navigation from gragh ");
        printf("\n🔹 'I' OR 'O' for zome in or out   ");
        printf("\n🔹 enter R to reset  ");
        printf("\n🔹 enter 0 to return menu:   ");

        navigation = getchar();
        ///scanf("%c", &navigation);
        if (navigation == 'd' || navigation == 'D')
        { 
            x_max += (x_max - x_min) / 10.0;
            x_min += (x_max - x_min) / 10.0;
        }
        else if (navigation == 'a' || navigation == 'A')
        {
            x_max -= (x_max - x_min) / 10.0;
            x_min -= (x_max - x_min) / 10.0;
        }
        else if (navigation == 'w' || navigation == 'W')
        {
            y_max += (y_max-y_min)/10;
            y_min += (y_max-y_min)/10;
        }
        else if (navigation == 's' || navigation == 'S')
        {
            y_max -= (y_max-y_min)/10;
            y_min -= (y_max-y_min)/10;
        }
        else if (navigation == 'o' || navigation == 'O')
        {
            y_max += (y_max-y_min)/10;
            y_min -= (y_max-y_min)/10;
            x_max += (x_max - x_min) / 10.0;
            x_min -= (x_max - x_min) / 10.0;
        }
        else if (navigation == 'i' || navigation == 'I')
        {
            y_max -= (y_max-y_min)/10;
            y_min += (y_max-y_min)/10;
            x_max -= (x_max - x_min) / 10.0;
            x_min += (x_max - x_min) / 10.0;
        }
        else if (navigation == 'r' || navigation == 'R')
        {
            x_min = x_min_copy;
            x_max = x_max_copy;
            y_min = y_min_copy;
            y_max = y_max_copy;
        }
        else if (navigation == '0')
        {
            run_plot = 0;
        }

    }
    

}


void clear_screen() {

#ifdef _WIN32
    system("cls");  // برای ویندوز
#else
    system("clear"); // برای لینوکس و مک
#endif
}

/// 
///  محاسباتی ها
/// 


double calculateFunction(const char *func, double value) {
    if (strcmp(func, "ans") == 0) return ANS((int)value); // 0
    else if (strcmp(func, "sqrt") == 0) 
        if (value >= 0)
            return sqrt(value);// 1
        else
        {
            printf("❌ Error: use ➖ under radical");
            exit(EXIT_FAILURE);
        }
    else if (strcmp(func, "sin") == 0)
    {   if (radin1_or_degree2 == 1)
            return sin(value);
        else
            return sin(value*pi/180);}// 2

    else if (strcmp(func, "arcsin") == 0)
    {   if (radin1_or_degree2 == 1)
            return asin(value);
        else
            return asin(value)*180/pi;}// 3

    else if (strcmp(func, "cos") == 0)
        {   if (radin1_or_degree2 == 1)
                return cos(value);
            else
                return cos(value*pi/180);}// 4

    else if (strcmp(func, "arccos") == 0)
        {   if (radin1_or_degree2 == 1)
                return acos(value);
            else
                return acos(value)*180/pi;}// 5

    else if (strcmp(func, "tan") == 0)
    {   if (radin1_or_degree2 == 1)
            return tan(value);
        else
            return tan(value*pi/180);}// 6

    else if (strcmp(func, "arctan") == 0)
    {   if (radin1_or_degree2 == 1)
            return atan(value);
        else
            return atan(value)*180/pi;}// 7 

    else if (strcmp(func, "cot") == 0)
    {   if (radin1_or_degree2 == 1)
            return 1/tan(value);
        else
            return 1/tan(value*pi/180);}// 8

    else if (strcmp(func, "arccot") == 0)
    {   if (radin1_or_degree2 == 1)
            return atan(1/value);
        else
            return atan(1/value)*180/pi;}// 9

    else if (strcmp(func, "log") == 0) return log10(value); // 10
    else if (strcmp(func, "exp") == 0) return exp(value); // 11
    else if (strcmp(func, "ln") == 0) return log(value); // 12
    else if (strcmp(func, "abs") == 0) return fabs(value); // 13
    else if (strcmp(func, "fact") == 0) return fact(value);// 14
    else if (strcmp(func, "rnd") == 0) return rand(); // 16
    
    
    else{
        printf("❌ Error: Unknown function '%s'!❌\n", func);}
    exit(EXIT_FAILURE);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default:
            printf("❌Error: Unknown operator '%c'!❌\n", op);
            exit(EXIT_FAILURE);
    }
}

double evaluateSimpleExpression(const char *expression) {
    double numbers[MAX_EXPR_LEN];
    char operators[MAX_EXPR_LEN];
    int numTop = -1, opTop = -1;

    int i = 0;
    while (expression[i] != '\0') {
        if (isdigit(expression[i]) || expression[i] == '.' || (expression[i] == '-' && (i == 0 || isOperator(expression[i - 1])))) {
            // Handle numbers, including negative numbers
            char buffer[MAX_EXPR_LEN];
            int j = 0;
            if (expression[i] == '-') buffer[j++] = expression[i++];
            while (isdigit(expression[i]) || expression[i] == '.') {
                buffer[j++] = expression[i++];
            }
            buffer[j] = '\0';
            numbers[++numTop] = atof(buffer);
        } else if (isOperator(expression[i])) {
            // Ensure correct precedence for operators
            while (opTop != -1 && precedence(operators[opTop]) >= precedence(expression[i])) {
                char op = operators[opTop--];
                double b = numbers[numTop--];
                double a = numbers[numTop--];
                numbers[++numTop] = applyOperator(a, b, op);
            }
            operators[++opTop] = expression[i++];
        } else {
            i++;
        }
    }

    while (opTop != -1) {
        char op = operators[opTop--];
        double b = numbers[numTop--];
        double a = numbers[numTop--];
        numbers[++numTop] = applyOperator(a, b, op);
    }

    return numbers[numTop];
}

double calculateExpression(const char *expression) {
    char buffer[MAX_EXPR_LEN];
    int i = 0, j = 0;

    while (expression[i] != '\0') {
        if (expression[i] == '(') {
            int depth = 1;
            int start = ++i;
            while (depth > 0 && expression[i] != '\0') {
                if (expression[i] == '(') depth++;
                if (expression[i] == ')') depth--;
                i++;
            }

            if (depth != 0) {
                printf("❌Error: Mismatched parentheses!❌\n");
                exit(EXIT_FAILURE);
            }

            char subExpr[MAX_EXPR_LEN];
            strncpy(subExpr, &expression[start], i - start - 1);
            subExpr[i - start - 1] = '\0';
            double value = calculateExpression(subExpr);

            snprintf(&buffer[j], MAX_EXPR_LEN - j, "%f", value);
            j = strlen(buffer);
        } else if (isalpha(expression[i])) {
            char func[MAX_EXPR_LEN];
            int k = 0;
            while (isalpha(expression[i])) {
                func[k++] = expression[i++];
            }
            func[k] = '\0';

            if (expression[i] == '(') {
                int depth = 1;
                int start = ++i;
                while (depth > 0 && expression[i] != '\0') {
                    if (expression[i] == '(') depth++;
                    if (expression[i] == ')') depth--;
                    i++;
                }

                if (depth != 0) {
                    printf("❌Error: Mismatched parentheses!❌\n");
                    exit(EXIT_FAILURE);
                }

                char subExpr[MAX_EXPR_LEN];
                strncpy(subExpr, &expression[start], i - start - 1);
                subExpr[i - start - 1] = '\0';
                double value = calculateExpression(subExpr);

                if (expression[i] == '^') {
                    i++; // Skip the '^'
                    char expBuffer[MAX_EXPR_LEN];
                    int l = 0;

                    // Extract the exponent as a sub-expression
                    while (expression[i] != '\0' && (isdigit(expression[i]) || expression[i] == '.' || expression[i] == '(' || expression[i] == ')')) {
                        expBuffer[l++] = expression[i++];
                    }
                    expBuffer[l] = '\0';

                    // Calculate the exponent as a full expression
                    double exponent = calculateExpression(expBuffer);
                    value = pow(calculateFunction(func, value), exponent);
                } else {
                    value = calculateFunction(func, value);
                }


                snprintf(&buffer[j], MAX_EXPR_LEN - j, "%f", value);
                j = strlen(buffer);
            } else {
                printf("❌Error: Missing parentheses for function '%s'!❌\n", func);
                exit(EXIT_FAILURE);
            }
        } else {
            buffer[j++] = expression[i++];
        }
    }

    buffer[j] = '\0';
    return evaluateSimpleExpression(buffer);
}

double fact(double x){
    double y=1;
    for (double i = 1; i < 1+x ; i++)
    {
        y*=i;
    }
    return y;
}

void removeSpaces(char *str) {
    int i = 0, j = 0;


    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }


    str[j] = '\0';
}

double ANS (int x){
    int history_count = load_history(filename,history,res);
    if ((int)x > 0 && (int)x <= history_count )
    {
        return res[(int)(x-1)] ;
    } 
    else if ( (int)(x) == 0)
    {
        return res[history_count-1] ;
    }
    else
    {
        printf("\n❌ you can't use it :) but i use the last one ❌\n ");
        return res[history_count-1] ;
    }
}

void replacePiWithPiValue(char *str) {
    char temp[256];
    int i = 0, j = 0;

    while (str[i] != '\0') {
        // بررسی دو حرف "pi"
        if (str[i] == 'p' && str[i+1] == 'i') {
            // جایگزینی "pi" با عدد پی
            j += sprintf(&temp[j], "%.5f\n", pi); 
            i += 2; // پرش به دو حرف بعدی
        } else {
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0'; // پایان رشته

    // کپی کردن نتیجه به رشته اصلی
    strcpy(str, temp);
}

void replace_E_With_neper_Value(char *str) {
    char temp[256];
    int i = 0, j = 0;

    while (str[i] != '\0') {
        // بررسی e
        if (str[i] == 'e' && str[i+1] != 'x') {
            // جایگزین با نپر
            j += sprintf(&temp[j], "%.5f\n", e); 
            i += 1; // پرش به دو حرف بعدی
        } else {
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0'; // پایان رشته

    // کپی کردن نتیجه به رشته اصلی
    strcpy(str, temp);
}
void make_manfi_dar_manfi_to_mosbat(char *str) {
    char temp[256];
    int i = 0, j = 0;

    while (str[i] != '\0') {
        // بررسی دو حرف "pi"
        if (str[i] == '-' && str[i+1] == '-') {
            // جایگزینی "pi" با عدد پی
            j += sprintf(&temp[j], "%c\n", '+'); 
            i += 2; // پرش به دو حرف بعدی
        } else {
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0'; // پایان رشته

    // کپی کردن نتیجه به رشته اصلی
    strcpy(str, temp);
}

///
/// nemodar
///

void replace_x_with_number(char* str, double num) {
    char temp[256]; // یک آرایه موقتی برای ذخیره رشته جدید
    int j = 0;
    
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 'x'&& str[i-1]!='e') {
            // جایگزینی 'x' با عدد
            j += sprintf(temp + j, "%.2f", num); 
        } else {
            temp[j++] = str[i]; // کپی کردن سایر کاراکترها
        }
    }
    temp[j] = '\0'; // اتمام رشته
    strcpy(str, temp); // بازنویسی رشته اصلی
}

void draw_plot(double x_min, double x_max, double x_values[], double y_min, double y_max, double y_values[], int count,char input[]) {
    

    char plot[HEIGHT + 2][WIDTH + 2]; // ماتریس برای ذخیره نمودار (شامل کادر)

    // پر کردن فضای نمودار با کاراکتر فاصله
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            plot[i][j] = ' ';
        }
    }

    // رسم کادر اطراف نمودار
    for (int i = 1; i <= HEIGHT; i++) {
        plot[i][0] = '|';             // کادر سمت چپ
        plot[i][WIDTH + 1] = '|';     // کادر سمت راست
    }

    for (int j = 0; j <= WIDTH + 1; j++) {
        plot[0][j] = '-';             // کادر بالا
    }
    for (int j = 0; j <= WIDTH + 1; j++) {
        plot[HEIGHT + 1][j] = '-';    // کادر پایین
    }
    plot[0][0] = plot[0][WIDTH + 1] = '+';             // گوشه‌های بالا
    plot[HEIGHT + 1][0] = plot[HEIGHT + 1][WIDTH + 1] = '+'; // گوشه‌های پایین

    // رسم نقاط نمودار
    for (int i = 0; i < count; i++) {
        double x = x_values[i];
        double y = y_values[i];

        // نرمال‌سازی مقادیر x و y به محدوده نمودار
        int px = (int)((x - x_min) / (x_max - x_min) * (WIDTH - 1)) + 1; 
        int py = (int)((y - y_min) / (y_max - y_min) * (HEIGHT - 1)) + 1;

        // تبدیل مختصات به مختصات ماتریس
        py = HEIGHT - py + 1; // معکوس کردن محور y برای مطابقت با کنسول

        // اطمینان از اینکه مختصات در محدوده نمودار هستند
        if (px >= 1 && px <= WIDTH && py >= 1 && py <= HEIGHT) {
            plot[py][px] = '*'; // علامت‌گذاری نقطه
        }
    }

    // چاپ نمودار با کادر و تقسیمات
    for (int i = 0; i <= HEIGHT + 1; i++) {
        // چاپ مقادیر y در کنار کادر
        if (i >= 1 && i <= HEIGHT) {
            double y_value = y_max - (i - 1) * (y_max - y_min) / (HEIGHT - 1);
            if ((i - 1) % (HEIGHT / TICKS) == 0) {
                printf("%10.2lf |", y_value);
            } else {
                printf("           |");
            }
        } else {
            printf("            ");
        }

        // چاپ نمودار
        for (int j = 0; j <= WIDTH + 1; j++) {
            
            if (plot[i][j] == '*')
            {
                printf("\033[1;36m");
                printf("*");
                printf("\033[0m");
            }
            else{
                putchar(plot[i][j]);}            
        }
        putchar('\n');
    }

    // چاپ مقادیر x در زیر نمودار
    printf("    ");
    for (int j = 0; j < TICKS; j++) {
        double x_value = x_min +(j*( ( x_max - x_min)/(TICKS-1)));
        printf("%11.3lf", x_value);  // نمایش مقادیر در تقسیمات مشخص
        printf("    ");
    }
    printf("\n");

    

}

void findMinMax(double arr[], int size, double *min, double *max) {
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

///
/// save
///

// تابع ذخیره محاسبه در فایل
void save_to_history(const char *filename, const char *history, double res) {
    FILE *file = fopen(filename, "a"); // حالت append
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fprintf(file, "%s %.10lf\n", history, res);
    fclose(file);
}

void clear_history(const char *filename) {
    FILE *file = fopen(filename, "w"); // حالت write برای بازنویسی فایل
    if (file == NULL) {
        printf("❌ Error opening file for clearing ❌");
        return;
    }
    fclose(file);
    printf("👍 : History cleared successfully.\n");
}
// تابع بارگذاری تاریخچه از فایل
int load_history(const char *filename, char history[MAX_HISTORY][256], double res[MAX_HISTORY]) {
    FILE *file = fopen(filename, "r"); // باز کردن فایل برای خواندن
    if (file == NULL) {
        // اگر فایل پیدا نشد
        printf("No history file found. A new file will be created.\n");
        return 0;
    }

    int count = 0;
    char line[256]; // برای خواندن هر خط

    while (fgets(line, sizeof(line), file) != NULL) {
        // خط جاری را به عنوان رشته ذخیره می‌کنیم
        line[strcspn(line, "\n")] = 0; // حذف کاراکتر '\n' انتهای خط
        strncpy(history[count], line, 256); // ذخیره رشته در history

        // خواندن خط بعدی برای عدد
        if (fgets(line, sizeof(line), file) != NULL) {
            double value;
            if (sscanf(line, "%lf", &value) == 1) {
                res[count] = value; // ذخیره مقدار عددی در res
                count++;

                // جلوگیری از تجاوز به آرایه
                if (count >= MAX_HISTORY) {
                    break;
                }
            }
        }
    }

    fclose(file);
    return count; // تعداد آیتم‌های لود شده
}

