package android.os;

interface ICDEService {
	void write_mem(String mem);
	String read_mem();
}