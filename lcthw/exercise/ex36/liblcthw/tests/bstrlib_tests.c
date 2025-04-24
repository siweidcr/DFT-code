#include "minunit.h"
#include <lcthw/bstrlib.h>

void *test_bstrlib() {

/* struct tagbstring {
               int mlen;
               int slen;
   unsigned char * data;
};

mlen 表示为数据字段分配的内存的下限。 slen 表示 bstring 的确切长度。data 是一个连续的无符号字符缓冲区。最小的正确性检查是：(slen >= 0 && mlen >= slen && data != NULL)。
 */

/*  bstring bfromcstr (const char * str)
 *
 *  Create a bstring which contains the contents of the '\0' terminated char *
 *  buffer str.
 */
    bstring btext = bfromcstr("hello,we are the world!");
    check(btext != NULL, "wrong in creating bstring!");
    printf("mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);

    int a = bdestroy(btext);
    check(a == BSTR_OK, "wrong in destroy btext!");
/*  bstring blk2bstr (const void * blk, int len)
 *
 *  Create a bstring which contains the content of the block blk of length
 *  len.
 */
    btext = blk2bstr("hello, world!", 5);
    check(btext != NULL, "wrong in creating blk bstring!");
    printf("mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);

    a = bdestroy(btext);
    check(a == BSTR_OK, "wrong in destroy blk btext!");
/*  bstring bstrcpy (const_bstring b)
 *
 *  Create a copy of the bstring b.
 */
    btext = bfromcstr("forgrademe ,yes!");
    bstring btext_copy = bstrcpy(btext);
    check(btext != NULL, "wrong string copy");
    printf("copy from btext: mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
    printf("copy to btext_copy: mlen:%d,slen:%d,string:%s\n",btext_copy->mlen,btext_copy->slen,btext_copy->data);

    a = bdestroy(btext_copy);
    check(a == BSTR_OK, "wrong in destroy btext_copy!");
/*  int bassign (bstring a, const_bstring b)
 *
 *  Overwrite the string a with the contents of string b.
 */
    bstring btext_assign = bfromcstr("forgrademe ,no!"); 
    a = bassign(btext, btext_assign);
    check(a == BSTR_OK, "wrong in assign btext");
    printf("overwrite new btext: mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
    a = bdestroy(btext_assign);
    check(a == BSTR_OK, "wrong in destroy btext_assign");
/*  int bassigncstr (bstring a, const char * str)
 *
 *  Overwrite the string a with the contents of char * string str.  Note that
 *  the bstring a must be a well defined and writable bstring.  If an error
 *  occurs BSTR_ERR is returned however a may be partially overwritten.
 */
    a = bassigncstr(btext, "forgrademe ,nice!");
    check(a == BSTR_OK, "wrong in assign btext with c str");
    printf("overwrite new btext: mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
/*  int bassignblk (bstring a, const void * s, int len)
 *
 *  Overwrite the string a with the contents of the block (s, len).  Note that
 *  the bstring a must be a well defined and writable bstring.  If an error
 *  occurs BSTR_ERR is returned and a is not overwritten.
 */
    a = bassignblk(btext, "forgrademe ,not bad!!!",20);
    check(a == BSTR_OK, "wrong in assign btext with c str with length");
    printf("overwrite new btext: mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
/*  int bconcat (bstring b0, const_bstring b1)
 *
 *  Concatenate the bstring b1 to the bstring b0.
 */
    bstring btext_concat = bfromcstr("!!");
    a = bconcat(btext, btext_concat);
    check(a == BSTR_OK, "wrong in concat btext_concat to btext");
    printf("new btext: mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);

    a = bdestroy(btext_concat);
    check(a == BSTR_OK, "wrong in destroy btext_concat");
/*  int bstricmp (const_bstring b0, const_bstring b1)
 *
 *  Compare two strings without differentiating between case.  The return
 *  value is the difference of the values of the characters where the two
 *  strings first differ after lower case transformation, otherwise 0 is
 *  returned indicating that the strings are equal.  If the lengths are
 *  different, then a difference from 0 is given, but if the first extra
 *  character is '\0', then it is taken to be the value UCHAR_MAX+1.
 */
    bstring btext_cmp = bfromcstr("\0");
    check(btext_cmp != NULL, "wrong in creating bstring btext_cmp: blank!");
    printf("mlen:%d,slen:%d,string:%s\n",btext_cmp->mlen,btext_cmp->slen,btext_cmp->data);

    if(bstricmp(btext, btext_cmp) > 0){
        printf("btext > btext_cmp\n");
    }
    else if(bstricmp(btext, btext_cmp) == 0){
	printf("btext equal to btext_cmp\n");
	}
    else{
	printf("btext < btext_cmp\n");
	}
/*  int biseq (const_bstring b0, const_bstring b1)
 *
 *  Compare the string b0 and b1.  If the strings differ, 0 is returned, if
 *  the strings are the same, 1 is returned, if there is an error, -1 is
 *  returned.  If the length of the strings are different, this function is
 *  O(1).  '\0' termination characters are not treated in any special way.
 */
    bassigncstr(btext_cmp,"forgrademe");
    if(biseq(btext, btext_cmp) == 0){
        printf("the two strings are different!\n");
    }
    else if(biseq(btext, btext_cmp) == 1){
        printf("the two strings are the same!\n");
    }
    else if(biseq(btext, btext_cmp) == -1){
        log_err("an message occur in compare btext and btext_cmp\n");
    }
/*  int bfindreplace (bstring b, const_bstring find, const_bstring repl,
 *                    int pos)
 *
 *  Replace all occurrences of a find string with a replace string after a
 *  given point in a bstring.
 */ 
    bstring btext_repl = bfromcstr("4dddr");
    bfindreplace(btext, btext_cmp, btext_repl, 0);

    printf("mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
    
    bdestroy(btext_repl);
    bdestroy(btext_cmp);
/*  struct bstrList * bsplit (const_bstring str, unsigned char splitChar)
 *
 *  Create an array of sequential substrings from str divided by the character
 *  splitChar.
 */
    a = bassigncstr(btext, "forgrademe ,nice!, to make test of, bsplit");
    check(a == BSTR_OK, "wrong in assign btext");
    printf("mlen:%d,slen:%d,string:%s\n",btext->mlen,btext->slen,btext->data);
    struct bstrList *List = bsplit(btext, 'm');
    check(List != NULL, "wrong in split str");
    printf("qty:%d,mlen:%d\n",List->qty,List->mlen);
    int i;
    for(i = 0; i < List->qty ; i++){
    	printf("mlen:%d,slen:%d,data:%s\n",List->entry[i]->mlen,List->entry[i]->slen,List->entry[i]->data);
    }
    a = bstrListDestroy(List);
    check(a == BSTR_OK, "wrong in destroy bstrList");
/*  bstring bformat (const char * fmt, ...)
 *
 *  Takes the same parameters as printf (), but rather than outputting results
 *  to stdio, it forms a bstring which contains what would have been output.
 *  Note that if there is an early generation of a '\0' character, the
 *  bstring will be truncated to this end point.
 */
    bstring btext_format = bformat("test bformat: a=%d",a);   
    check(btext_format != NULL, "wrong bformat use");
    printf("mlen:%d,slen:%d,string:%s\n",btext_format->mlen,btext_format->slen,btext_format->data);
error:
    return 0;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bstrlib);

    return NULL;
}

RUN_TESTS(all_tests);
