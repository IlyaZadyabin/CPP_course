#include <string>
#include "test_runner.h"
#include <list>
using namespace std;

class Editor {
public:
	// Реализуйте конструктор по умолчанию и объявленные методы
	Editor() = default;
	void Left() {
		if (mouse_pos != text.begin()) {
			mouse_pos--;
		}
	}
	void Right() {
		if (mouse_pos != text.end()) {
			mouse_pos++;
		}
	}
	void Insert(char token) {
		mouse_pos = text.insert(mouse_pos, token);
		mouse_pos++;
	}
	void Cut(size_t tokens = 1) {
		auto tmp_it = mouse_pos;
		int flag = 0;
		if (mouse_pos != text.begin()) {
			tmp_it = prev(mouse_pos);
			flag = 1;
		} else {
			tmp_it = next(mouse_pos, tokens);
		}

		auto last = mouse_pos;
		for(auto i = 0; i < tokens && last != text.end(); i++) {
			advance(last, 1);
		}

		buffer.splice(buffer.begin(), text, mouse_pos, last);
		mouse_pos = flag ? next(tmp_it) : tmp_it;
	}
	void Copy(size_t tokens = 1) {
		auto last = mouse_pos;
		for(auto i = 0; i < tokens && last != text.end(); i++) {
			advance(last, 1);
		}
		buffer = {mouse_pos, last};
	}
	void Paste() {
		text.insert(mouse_pos, buffer.begin(), buffer.end());
	}
	string GetText() const {
		return {text.begin(), text.end()};
	}

private:
	list<char> text;
	list<char> buffer;
	_List_iterator<char> mouse_pos{text.begin()};
};

void TypeText(Editor& editor, const string& text) {
	for(char c : text) {
		editor.Insert(c);
	}
}

void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for(size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);
		for(size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const string text = "esreveR";
	for(char c : text) {
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	return 0;
}