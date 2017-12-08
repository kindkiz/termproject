//파일속의 키워드 찾기
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
	struct file arr[1000];		//키워드있는 파일들만 넣고 솔팅하기 위함.
	char test[50];                 //strstr로 테스트할것 키워드가 있는지 없는지
	char mysearch[50];         //keyward
	long handle;
	int result = 1, count= 0;   //count는 키워드가 있는 파일이 몇개인지 알기 위함이다.
	clock_t start, end;
	rewind(stdin);
	scanf("%s",&mysearch);   //keyward를 scanf로 받아온다.
	//strcpy(mysearch, argv[1]);
	start = clock();

	handle = _findfirst("C:\\Users\\한태균\\Desktop\\dataset\\*.txt", &fd);
	if (handle == -1) {
		printf("망함");
		return 0;
	}
	while (result != -1) {		// 여기서 키워드 있는것들 찾고 배열에 넣는것까지 할거야
		arr[count].keyward = 0;
		FILE* fp = fopen(fd.name, "rt");
		while (!feof(fp)) {
			fscanf(fp, "%s", test);
			if (stristr(test,mysearch)!= NULL) {       // keyward 개수 세기
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
	//여기까지 키워드 몇개인지 찾고 배열에 넣었다.

	/*qsort를 사용해볼까*/

	qsort(arr, count, sizeof(struct file), compare); //keyward수를 기준으로 오름차순 정렬

	puts("제목 \t\t\t 빈도\n");

	for (int i = 0; i < count; i++) {
		printf("%s \t <%d>\n", arr[i].name, arr[i].keyward);
	}

	end = clock();
	printf("\ntime:%.2f초", (double)(end-start)/1000);
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

char* stristr(const char* string, const char* strSearch) {    // 대소문자 구분없이 strstr
	const char*s, *sub;

	for (; *string; string++) {
		for (sub = strSearch, s = string; *sub && *s; sub++, s++) {
			if (tolower(*s) != tolower(*sub)) break;
		}
		if (*sub == 0) return (char*)string;
	}
	return NULL;
}