#include <iostream>
#include <exception>
#include <cstring>

using namespace std;

#define MAX(a, b) (((a)>(b)?(a):(b)))

class String {
	unsigned size_;
	unsigned capacity_;
	char* buffer_;

	friend ostream& operator<<(ostream&, const String&);	

	void ensure_capacity(unsigned cap) {
		if(size_ + cap > capacity_) {
			return;
		}
		unsigned new_capacity = MAX(size_ + cap + 1 , capacity_ * 2);
		char* old_buffer = buffer_;
		buffer_ = new char[new_capacity];
		strcpy(buffer_, old_buffer);
		delete [] old_buffer;
	}

public:
	explicit String(int capacity = 0)
	: size_(0),
	  capacity_(capacity),
	  buffer_(new char [capacity_])
	{}

	String(const char* str)
	: size_(strlen(str)),
	  capacity_(size_ + 1),
	  buffer_(new char [capacity_])
	{
		strcpy( buffer_ , str );
	}

	~String() {
		delete [] buffer_;
	}

	String(const String& other)
	: size_(other.size_),
	  capacity_(other.capacity_),
	  buffer_(new char [capacity_])
	{
		strcpy( buffer_ , other.buffer_ );
	}

	unsigned size() const {
		return size_;
	}

	void push_back(char ch) {
		ensure_capacity(1);
		buffer_[size_++] = ch;
		buffer_[size_]= '\0';
	}

	String& operator += (const String& other) {
		ensure_capacity(other.size_);
		strcpy(buffer_ + size_ , other.buffer_);
		size_ += other.size_;
	}

	char& operator[](unsigned index) {
		return buffer_[index];
	}

	char& at (unsigned index) {
		if(index>size_) {
			throw exception();
		}
	}
		

};

ostream& operator<<(ostream& out, const String& str) {
	if (str.size_ > 0) {
		out << str.buffer_;
	}
	return out;
}

String& operator+(const String& str1, const String& str2) {
	String res = str1;
	res += str2;
	return res;
}

int main() {
	String str("Hello World!");
	cout << str << endl;

	return 0;
}
