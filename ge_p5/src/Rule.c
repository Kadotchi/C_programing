/*
 * Rule.c
 *
 *  Created on: 2021/05/20
 *      Author: kador
 */

#include<stdio.h>

void Rule() {
	FILE *fp;
	char str[256];
	fp = fopen("Rule_explanation_p5.txt", "r");

	if(fp==NULL){
		printf("ファイルの読み込み失敗\n");
	}else {
			while (!feof(fp)) {
			fgets(str, 256, fp);
			printf("%s", str);
		}
	}
	fclose(fp);
	printf("\n");
}
