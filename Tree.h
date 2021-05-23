#pragma once
#include <string>
#include <iostream>
#include <time.h>

struct List_Item {
	std::string key;
	List_Item* next;
};

struct Hash_Item {
	List_Item* begin;
	List_Item* end;
	std::string key;
	Hash_Item() {
		begin = NULL;
		end = NULL;
		key = "";
	}
};

int N = 10;
int m = 12;
Hash_Item* Hash_table;


int h(std::string str) {
	int res = 0;
	for (int i = 0; i < str.length(); ++i) {
		res += int(str[i]);
	}
	return res % m;
}


int Add(std::string key, Hash_Item* a = Hash_table) {
	List_Item* temp = new List_Item();
	temp->key = key;
	temp->next = NULL;
	int res = h(key);
	int compare = 0;
	if (a[res].key == "") { a[res].key = key; compare++; }
	else if (a[res].key != key) {
		compare++;
		if (a[res].begin == NULL) {
			a[res].begin = temp;
			a[res].end = temp;
		}
		else {
			a[res].end->next = temp;
			a[res].end = temp;
		}
		compare++;
	}
	else if (a[res].key == key) { return -1; }
	return compare;
}


int Search(std::string key, Hash_Item* a = Hash_table) {
	int res = h(key);
	int compare = 0;
	if (a[res].key != "") {
		if (a[res].key == key) {
			compare++;
			return compare;
		}
		else{
			compare++;
			List_Item* pCurrent = a[res].begin;
			while (pCurrent != NULL) {
				compare++;
				if (pCurrent->key == key) { return compare; }
				pCurrent = pCurrent->next;
			}
		}
	}
	return -1;
}


std::string Show(Hash_Item* a = Hash_table) {
	std::string str = "";
	for (int i = 0; i < m; ++i) {
		str += "\nA[" + std::to_string(i) + "] = " + a[i].key + " | ";
		List_Item* pCurrent = a[i].begin;
		while (pCurrent != NULL) {
			str += pCurrent->key + " | ";
			pCurrent = pCurrent->next;
		}
	}
	return str;
}

int Delete(std::string key, Hash_Item* a = Hash_table) {
	int res = h(key);
	int compare = 0;
	if (a[res].key == key) {
		if (a[res].begin == NULL) { a[res].key = ""; }
		else {
			a[res].key = a[res].begin->key;
			List_Item* temp = a[res].begin;
			a[res].begin = temp->next;
			delete(temp);
		}
		return 1;
	}
	else {
		List_Item* pCurrent = a[res].begin;
		if (pCurrent->key == key) {
			List_Item* temp = a[res].begin;
			a[res].begin = temp->next;
			delete(temp);
			return 1;
		}
		else {
			List_Item* pPred = pCurrent;
			pCurrent = pCurrent->next;
			while (pCurrent != NULL) {
				if (pCurrent->key == key) {
					pPred->next = pCurrent->next;
					delete(pCurrent);
					return 1;
				}
				pPred = pCurrent;
				pCurrent = pCurrent->next;
			}
		}
		return -1;
	}
}