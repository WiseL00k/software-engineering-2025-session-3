### ������̵�������ҵ���������Ŀ
| �����ҵ�����ĸ��γ� | [�༶������](https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience)|
|--------|-------|
| �����ҵҪ�������� | [��ҵҪ�������](https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience/homework/13470) |
| �����ҵ��Ŀ�� | ʵ��һ���Զ�����Сѧ����������Ŀ�������г��� |


### ���ߣ������� ����Դ3123004146

### Github��Ŀ��ַ:

### һ��PSP���

| PSP2.1 | Personal Software Process Stages | Ԥ����ʱ�����ӣ�| ʵ�ʺ�ʱ�����ӣ�|
| ----------------- |--------------- |---------------|---------------|
|Planning| �ƻ� | 35 | 30 |
| �� Estimate | �� �������������Ҫ����ʱ�� | 35 | 30 |
| Development | ���� | 300 | 348 |
| �� Analysis | �� ������� (����ѧϰ�¼���) | 40 | 50 |
| �� Design Spec  | �� ��������ĵ� | 35 | 40 |
| �� Design Review | �� ��Ƹ��� | 25 | 20 |
| �� Coding Standard | �� ����淶 (ΪĿǰ�Ŀ����ƶ����ʵĹ淶) | 30 | 35 |
| �� Design | �� ������� | 40 | 45 |
| �� Coding | �� ������� | 70 | 85 |
| �� Code Review | �� ���븴�� | 30 | 35 |
|�� Test  | �� ���ԣ����Ҳ��ԣ��޸Ĵ��룬�ύ�޸ģ� | 30 | 38 |
|Reporting  | ���� | 73 | 93 |
| �� Test Repor | �� ���Ա���  | 35 | 46 |
| �� Size Measurement | �� ���㹤���� | 18 | 22 |
| �� Postmortem & Process Improvement Plan |�� �º��ܽ�, ��������̸Ľ��ƻ�  | 20 | 25 |
| | �� �ϼ�  | 408 | 471 |

### ����Ч�ܷ���

### �������ʵ�ֹ���
#### ������֯�ṹ
����Ŀ�������������ƣ�ͨ�������Эͬ����ʵ�ַ���������Ŀ�������Զ����Ĺ��ܡ�����ṹ������ְ���������ģ������ϸ��ھۡ�

##### ���������
![exported_image (1)](https://img2024.cnblogs.com/blog/3699561/202510/3699561-20251019161015536-1824417740.png)

#### ���ϵ˵��
1.**������ϵ**��
- `App` �ǳ�����ڣ�Э�� `QuizGenerator` �� `AnswerChecker` ����
- `QuizGenerator` ������������ `Expression` ����
- `Expression` ���� `Fraction` ������ֵ���㣬���� `Utils` �������������
- `AnswerChecker` ���� `Fraction` ���д𰸱ȶԣ����� `Utils` �����ַ�������

2.**ְ�𻮷�**��
- ���߲� ��`Utils` �ṩͨ�ù��ܣ���������ַ����ָ
- ���ݲ� ��`Fraction` ��װ�������ݼ�����
- ҵ��� ��`Expression` ������ʽ�߼���`QuizGenerator` ������Ŀ����
- ���Ʋ� ��`App` ���������в��������̿��ƣ�`AnswerChecker` ���������߼�

| ģ��            | ����                     | ��Ҫְ��     |
| --------------- | ------------------------ | ------------ |
| `Fraction`      | �����������������       | �������ݽṹ |
| `Expression`    | ��������㵥���������ʽ | ���ʽ�߼��� |
| `QuizGenerator` | ����������Ŀ����ļ�   | ��Ŀ�����   |
| `AnswerChecker` | �ж�����ȷ���         | �����ͳ��   |
| `Utils`         | �ṩͨ�ù���             | ֧�Ź���     |
| `App`           | ���������в����ȳ���     | �������߼�   |


#### �ؼ���������ͼ
**1. Expression::generateRandom��������ɱ��ʽ��**
![exported_image (2)](https://img2024.cnblogs.com/blog/3699561/202510/3699561-20251019163010405-1397293359.png)

**2. Expression::evaluate�����ʽ��ֵ��**
![exported_image (3)](https://img2024.cnblogs.com/blog/3699561/202510/3699561-20251019163109875-209327349.png)

**3. AnswerChecker::checkAnswers����У�飩**
![exported_image (4)](https://img2024.cnblogs.com/blog/3699561/202510/3699561-20251019163156306-1916827229.png)

**4. QuizGenerator::generateAll������������Ŀ��**
![exported_image](https://img2024.cnblogs.com/blog/3699561/202510/3699561-20251019160927383-2005991347.png)

#### ���ĺ���˵��
1.**Expression::generateRandom**��
�������ɷ���Ҫ���������ʽ��ȷ������Ǹ������ظ���ͨ����γ��Ի��ƴ�����Ч���ʽ
2.**Expression::evaluate**��
ʹ��˫ջ�㷨������ջ�������ջ��������������ʽ��������������ȼ���ȷ��������ȷ��
3.**Fraction ����������**��
ʵ�ַ������������㣬�Զ���������ȷ����ĸΪ��������������еĳ������
4.**AnswerChecker::checkAnswers**��
�Ա��û������׼�𰸣�֧��������������ʹ��������ָ�ʽ�����ַ����ȶ��ٽ���Ϊ�����ȶ�
5.**QuizGenerator::generateAll**��
��������ָ�������Ĳ��ظ����ʽ��ʹ�ü��Ͻ���ȥ�ع�����������Դ�����������ѭ��

### �ġ�����˵��
#### 1. Fraction �����ʵ�֣��������������

������������ϵͳ�Ļ������ݽṹ����������ı�ʾ������͸�ʽ����ȷ��������ֵ�����׼ȷ�ԡ�
```
// ��������ʵ��
void Fraction::simplify() {
    // �������������Ϊ0ʱ���̶���ĸΪ1��0/1��
    if (numerator == 0) {
        denominator = 1;
        return;
    }

    // ������ӷ�ĸ�����Լ����GCD�������ڻ���
    int common = gcd(numerator, denominator);
    numerator /= common;   // ���ӳ������Լ��
    denominator /= common; // ��ĸ�������Լ��

    // ȷ����ĸʼ��Ϊ����������ĸΪ�������ӷ�ĸͬʱȡ����
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}
```
˼·˵����
�����Ƿ�������ĺ�������ͨ�����Լ����GCD��ʵ�ַ���������ʾ������ͬһ�����Ĳ�ͬ��ʽ���� 2/4 �� 1/2��������Ϊ��ֵͬ��ͬʱǿ�Ʒ�ĸΪ��������֤��ʾ��Ψһ�ԡ�

```
// �����������أ�ȷ������Ǹ���
Fraction Fraction::operator-(const Fraction& other) const {
    // ����������ʽ��a/b - c/d = (ad - bc)/bd
    int newNum = numerator * other.denominator - other.numerator * denominator;
    int newDen = denominator * other.denominator;
    Fraction result(newNum, newDen); // �ȹ�����ʱ���

    // ����Լ����Сѧ����Ŀ��������������׳��쳣������Ч���ʽ
    if (result.toDouble() < 0) {
        throw runtime_error("�����������Ϊ����");
    }

    return result;
}
```
˼·˵�������ؼ��������ʱ������ʵ����ѧ���㣬��������ҵ��Լ�� ���� ȷ������Ǹ���ͨ���쳣���ƣ������ɱ��ʽʱ��ֱ�ӹ��˵�������Ҫ��ļ������㣨�� 3-5����

```
// ����ת�ַ�����֧�ִ�������ʾ��
string Fraction::toString() const {
    // �����������ĸΪ1����ֱ�ӷ��ط���
    if (denominator == 1) {
        return to_string(numerator); 
    }

    // �������������Ӿ���ֵ < ��ĸ������ʽΪ������/��ĸ��
    if (abs(numerator) < denominator) {
        return to_string(numerator) + "/" + to_string(denominator);
    }
    // ��������������Ӿ���ֵ >= ��ĸ������ʽΪ������'����/��ĸ��
    else {
        int whole = numerator / denominator;       // ��ȡ��������
        int remainder = abs(numerator % denominator); // ��ȡʣ����ӣ�ȡ����ֵ��
        if (remainder == 0) {
            return to_string(whole); // ��ʣ�����Ϊ0��ֱ�ӷ�������
        }
        return to_string(whole) + "'" + to_string(remainder) + "/" + to_string(denominator);
    }
}
```
˼·˵�������ݷ�����ʵ�ʴ�С���Զ�ת��Ϊ�����Сѧ��ϰ�ߵı�ʾ��ʽ����������������������������罫 3/2 ת��Ϊ ��1'1/2���������Ŀ�ɶ��ԡ�

#### 2. ���ʽ��������㣨����ҵ���߼���
Expression �ฺ��������ɷ���Ҫ�����ѧ���ʽ�����������������ӷ�����������Ŀ���ɵĹؼ���

```
// ������ɱ��ʽ
void Expression::generateRandom(int range, int maxOps) {
    vector<char> ops = {'+', '-', '*', '/'}; // ֧�ֵ������
    // ������������������1��maxOps����ȷ�����ʽ�����㣩
    int numOperators = Utils::randInt(maxOps) + 1;
    int numNumbers = numOperators + 1; // �������� = ��������� + 1

    vector<Fraction> numbers;  // �洢���ʽ�е�����
    vector<char> operators;    // �洢���ʽ�е������

    // �������֣������������
    for (int i = 0; i < numNumbers; i++) {
        // 50%��������������50%�������������
        if (Utils::randInt(2) == 0) {
            // ������������Χ[0, range)���ұ������Ϊ0��i>0ʱ���ֿ�����Ϊ������
            int num;
            do {
                num = Utils::randInt(range);
            } while (num == 0 && i > 0); // i=0ʱ����0����Ϊ������/��������
            numbers.push_back(Fraction(num, 1));
        } else {
            // �������������ĸ��Χ[2, range)�����ӷ�Χ[1, ��ĸ-1]
            int denom = Utils::randInt(range - 2) + 2; // ȷ����ĸ>=2
            int numer = Utils::randInt(denom - 1) + 1; // ȷ������<��ĸ
            numbers.push_back(Fraction(numer, denom));
        }
    }

    // �������������
    for (int i = 0; i < numOperators; i++) {
        int opIndex = Utils::randInt(ops.size()); // ���ѡ�������
        operators.push_back(ops[opIndex]);
    }

    // �������ʽ�ַ��������������������ƴ�ӣ��м�ӿո�ָ���
    stringstream ss;
    for (int i = 0; i < numNumbers; i++) {
        ss << numbers[i].toString(); // ƴ������
        if (i < numOperators) {
            ss << " " << operators[i] << " "; // ƴ����������ӿո�ָ���
        }
    }
    exprStr = ss.str(); // ������ʽ�ַ���

    // ��֤���ʽ��Ч�ԣ���ೢ��5�Σ���������ѭ����
    int attempts = 0;
    while (attempts < 5) {
        try {
            result = evaluate(); // ������ʽ���
            if (result.toDouble() >= 0) break; // ȷ������Ǹ�
        } catch (...) {
            // ������ʧ�ܣ��縺�����������ȣ����������ɱ��ʽ
            // ��ʡ�������������ֺ�������Ĵ��룬�߼�ͬ�ϣ�
        }
        attempts++;
    }
}
```
˼·˵����
���ʽ���ɲ��� ���ֲ���� + ��֤���ˡ� ���ԣ�������������ֺ����������ͨ��������֤���ʽ�Ƿ���Ч������Ǹ����޳���ȣ���ͨ����������Դ�����ƽ������Ժͳ����ȶ��ԣ�ȷ���������㹻��������Ч��Ŀ��

#### 3. ��У��ʵ�֣��Զ����ĺ��ģ�
��У����ʵ���Զ����ĵĹؼ�����Ҫ������ָ�ʽ�Ĵ����룬��׼ȷ�ж��Ƿ����׼��һ�¡�

```
// �Ƚ��û������׼��
bool compareAnswers(const string& userAnswer, const string& correctAnswer) {
    string userAns = userAnswer;
    string correctAns = correctAnswer;

    // Ԥ�����Ƴ����пո񣬼����û�����ʱ�Ŀո��硰1 / 2���͡�1/2����Ϊ��ͬ��
    userAns.erase(remove(userAns.begin(), userAns.end(), ' '), userAns.end());
    correctAns.erase(remove(correctAns.begin(), correctAns.end(), ' '), correctAns.end());

    // ����У�飺���ַ�����ȫһ�£�ֱ�ӷ�����ȷ
    if (userAns == correctAns) {
        return true;
    }

    // ���У�飺����ΪFraction�����Ƚϣ�����ȼ۷�������2/4��1/2��
    try {
        Fraction userFrac, correctFrac;

        // �����û���ΪFraction����
        if (userAns.find('/') != string::npos) { // ������/�����Ƿ���
            if (userAns.find('\'') != string::npos) { // ������'�����Ǵ���������1'1/2��
                size_t apostrophePos = userAns.find('\'');
                int whole = stoi(userAns.substr(0, apostrophePos)); // ��ȡ��������
                string fracPart = userAns.substr(apostrophePos + 1); // ��ȡ��������
                size_t slashPos = fracPart.find('/');
                int numer = stoi(fracPart.substr(0, slashPos)); // ��ȡ����
                int denom = stoi(fracPart.substr(slashPos + 1)); // ��ȡ��ĸ
                // ת��Ϊ�ٷ���������*��ĸ + ����
                userFrac = Fraction(whole * denom + numer, denom);
            } else { // ���������3/4��
                size_t slashPos = userAns.find('/');
                int numer = stoi(userAns.substr(0, slashPos));
                int denom = stoi(userAns.substr(slashPos + 1));
                userFrac = Fraction(numer, denom);
            }
        } else { // ��������5��
            userFrac = Fraction(stoi(userAns), 1);
        }

        // ������׼��ΪFraction�����߼�ͬ�ϣ�ʡ���ظ����룩
        // ...

        // �ؼ��������ȽϷ��Ӻͷ�ĸ��ȷ���ȼ۷����ж�Ϊ��ȷ
        userFrac.simplify();
        correctFrac.simplify();
        return userFrac.getNumerator() == correctFrac.getNumerator() &&
               userFrac.getDenominator() == correctFrac.getDenominator();
    } catch (...) {
        // ������ʧ�ܣ����ʽ���󣩣��ж�Ϊ����
        return false;
    }
}
```
˼·˵������У����� ��˫��У�顱 ���ԣ���ͨ���ַ����ȶԿ����ж���ȫһ�µ��������ͨ������Ϊ�������󲢻��򣬴���ȼ۷������� 2/4 �� 1/2�����ж���ͬʱ���ݶ��������ʽ�����ո����������������������������û����顣�쳣����ȷ����ʽ����Ĵ𰸱���ȷ�ж�Ϊ����

### �塢��������
### ������ĿС��

1. ģ�黯��ƽ�����ϣ���������Ч��
- ��Ŀ�ϸ��� �������㣨Fraction/Utils���� ҵ��㣨Expression/QuizGenerator/AnswerChecker���� ���Ʋ㣨App���� �ֲ���ƣ���ģ��ְ��һ���ӿ�����������Fraction���װ���з��������߼���Expression�������Fraction�Ľӿڼ���ʵ�ֱ��ʽ���㣬�����ע�����ڲ�ʵ�֡�
2. �쳣������Լ��У��ȷ����Ŀ�Ϸ���
- Fraction����������У�ͨ���쳣���ƹ��˸���������� 3-5����
- Expression�����ɱ��ʽʱ���������Ϊ 0��������������Ч�����
- AnswerChecker��֧�ֶ��ִ𰸸�ʽ�����ո����� / ���� / ����������ͨ�� ���ַ����ȶ� + ��������ȶԡ� ˫��У��ȷ������׼ȷ�ԡ�
3. ������������������
4. ������Ч�ʸ���
5. ���չ�����������

���ν����Ŀ��������˹������󣬸������������ᵽ ��1+1>2�� ��Э����ֵ ���� ͨ�����ƻ��������չ������������˴���������������˿���Ч�ʡ�ͬʱ����Ŀ�еĲ���ҲΪ�������������˱����飺����ȷ��Ҫ�Ͻ����ӿ�Լ��Ҫ������

