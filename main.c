//���ϼ��� Ű���� ã��
#include<stdio.h>
#include<io.h>
#include<string.h>
#include<time.h>


struct file {
	char name[260];
	int keyward;
};


int compare(const void* a, const void* b);

char* stristr(const char* string, const char* strSearch);

int main(int argc, char* argv[]) {
	struct _finddata_t fd;
	struct file arr[1000];		//Ű�����ִ� ���ϵ鸸 �ְ� �����ϱ� ����.
	char test[50];                 //strstr�� �׽�Ʈ�Ұ� Ű���尡 �ִ��� ������
	char mysearch[50];         //keyward
	long handle;
	int result = 1, count= 0;   //count�� Ű���尡 �ִ� ������ ����� �˱� �����̴�.
	clock_t start, end;
	rewind(stdin);
	scanf("%s",&mysearch);   //keyward�� scanf�� �޾ƿ´�.
	//strcpy(mysearch, argv[1]);
	start = clock();

	handle = _findfirst("C:\\Users\\���±�\\Desktop\\dataset\\*.txt", &fd);
	if (handle == -1) {
		printf("����");
		return 0;
	}
	while (result != -1) {		// ���⼭ Ű���� �ִ°͵� ã�� �迭�� �ִ°ͱ��� �Ұž�
		arr[count].keyward = 0;
		FILE* fp = fopen(fd.name, "rt");
		while (!feof(fp)) {
			fscanf(fp, "%s", test);
			if (stristr(test,mysearch)!= NULL) {       // keyward ���� ����
				arr[count].keyward++;
			}
		}

		if (0 != arr[count].keyward) {
			strcpy(arr[count].name, fd.name);
			count++;
		}
		
		fclose(fp);
		result = _findnext(handle, &fd);
	}
	//������� Ű���� ����� ã�� �迭�� �־���.

	/*qsort�� ����غ���*/

	qsort(arr, count, sizeof(struct file), compare); //keyward���� �������� �������� ����

	puts("���� \t\t\t ��\n");

	for (int i = 0; i < count; i++) {
		printf("%s \t <%d>\n", arr[i].name, arr[i].keyward);
	}

	end = clock();
	printf("\ntime:%.2f��", (double)(end-start)/1000);
	_findclose(handle);
	return 0;
}

int compare(const void* a, const void* b) {
	struct file* ptr_a = (struct file*)a;
	struct file* ptr_b = (struct file*)b;

	if (ptr_a->keyward < ptr_b->keyward)
		return 1;
	else if (ptr_a->keyward == ptr_b->keyward)
		return 0;
	else
		return -1;
}

char* stristr(const char* string, const char* strSearch) {    // ��ҹ��� ���о��� strstr
	const char*s, *sub;

	for (; *string; string++) {
		for (sub = strSearch, s = string; *sub && *s; sub++, s++) {
			if (tolower(*s) != tolower(*sub)) break;
		}
		if (*sub == 0) return (char*)string;
	}
	return NULL;
}