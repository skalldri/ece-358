
class Packet
{
public:
	Packet(unsigned int size, unsigned long long int start_tick);
	~Packet();
	
	void processing_complete(unsigned long long int end_tick);
	
private:
	unsigned int size;
	unsigned long long creation_tick;
	unsigned long long end_tick;
		
};
