/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 22:37:20 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 15:17:22 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkModule.hpp"

NetworkModule::NetworkModule(void) : AModule(),
	_bytesInDiff(-1),
	_bytesOutDiff(-1),
	_packetInDiff(-1),
	_packetOutDiff(-1),
	_bytesInNew(-1),
	_bytesOutNew(-1),
	_packetInNew(-1),
	_packetOutNew(-1),
	_bytesInOld(-1),
	_bytesOutOld(-1),
	_packetInOld(-1),
	_packetOutOld(-1)
{
	return ;
}

NetworkModule::NetworkModule(NetworkModule const &src) : AModule(src),
	_bytesInDiff(src.getBytesInDiff()),
	_bytesOutDiff(src.getBytesOutDiff()),
	_packetInDiff(src.getPacketInDiff()),
	_packetOutDiff(src.getPacketOutDiff()),
	_bytesInNew(src.getBytesInNew()),
	_bytesOutNew(src.getBytesOutNew()),
	_packetInNew(src.getPacketInNew()),
	_packetOutNew(src.getPacketOutNew()),
	_bytesInOld(src.getBytesInOld()),
	_bytesOutOld(src.getBytesOutOld()),
	_packetInOld(src.getPacketInOld()),
	_packetOutOld(src.getPacketOutOld())
{
	return ;
}

NetworkModule::NetworkModule(bool isActive, int ID, std::string name, int position, int len) :
	AModule(isActive, ID, name, position, len),
	_bytesInDiff(-1),
	_bytesOutDiff(-1),
	_packetInDiff(-1),
	_packetOutDiff(-1),
	_bytesInNew(-1),
	_bytesOutNew(-1),
	_packetInNew(-1),
	_packetOutNew(-1),
	_bytesInOld(-1),
	_bytesOutOld(-1),
	_packetInOld(-1),
	_packetOutOld(-1)
{
	return ;
}

NetworkModule::~NetworkModule(void)
{
	return ;
}

void				NetworkModule::updateSysInfo(void)
{
	int			mib[6];
	size_t		len;
	char		*buf;
	char		*lim;
	char 		*next;
	struct 		if_msghdr *ifm;

	mib[0]= CTL_NET;		// networking subsystem
	mib[1]= PF_ROUTE;		// type of information
	mib[2]= 0;				// protocol (IPPROTO_xxx)
	mib[3]= 0;				// address family
	mib[4]= NET_RT_IFLIST2;	// operation
	mib[5]= 0;
	sysctl(mib, 6, NULL, &len, NULL, 0);
	buf = new char[(sizeof(char) * len)];
	sysctl(mib, 6, buf, &len, NULL, 0);
	lim = buf + len;
	if (this->_packetOutNew != -1)
		this->_packetOutOld = this->_packetOutNew;
	if (this->_packetInNew != -1)
		this->_packetInOld = this->_packetInNew;
	if (this->_packetOutNew != -1)
		this->_bytesOutOld = this->_packetOutNew;
	if (this->_bytesInNew != -1)
		this->_bytesInOld = this->_bytesInNew;
	for (next = buf; next < lim;) {
		ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;

		if (ifm->ifm_type == RTM_IFINFO2) {
			struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;

			if(if2m->ifm_data.ifi_type!=18) {
				this->_packetOutNew	+= if2m->ifm_data.ifi_opackets;
				this->_packetInNew	+= if2m->ifm_data.ifi_ipackets;
				this->_bytesOutNew	+= if2m->ifm_data.ifi_obytes;
				this->_bytesInNew	+= if2m->ifm_data.ifi_ibytes;
			}
		}
	}
	if (this->_packetOutNew != -1 && this->_packetOutOld != -1)
		this->_packetOutDiff = this->_packetOutNew - this->_packetOutOld;
	else
		this->_packetOutDiff = -1;

	if (this->_packetInNew != -1 && this->_packetInOld != -1)
		this->_packetInDiff = this->_packetInNew - this->_packetInOld;
	else
		this->_packetInDiff = -1;

	if (this->_bytesOutNew != -1 && this->_bytesOutOld != -1)
		this->_bytesOutDiff = this->_packetOutNew - this->_packetOutOld;
	else
		this->_packetOutDiff = -1;

	if (this->_bytesInNew != -1 && this->_bytesInOld != -1)
		this->_bytesInDiff = this->_bytesInNew - this->_bytesInOld;
	else
		this->_bytesInDiff = -1;

	delete buf;
	return ;
}

DataStruct const		NetworkModule::getData(unsigned int n) const
{
	DataStruct	dataToReturn;

	if (n == 0)
	{
		double *ptr = new double;
		*ptr = this->_bytesInDiff;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Variation of inbound bytes since last update");
		return (dataToReturn);
	}
	else if (n == 1)
	{
		double *ptr = new double;
		*ptr = this->_bytesOutDiff;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Variation of outbound bytes since last update");
		return (dataToReturn);	
	}
	else if (n == 2)
	{
		long int *ptr = new long int;
		*ptr = this->_packetInDiff;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Variation of inbound packets since last update");
		return (dataToReturn);
	}
	else if (n == 3)
	{
		long int *ptr = new long int;
		*ptr = this->_packetOutDiff;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Variation of outbound packets since last update");
		return (dataToReturn);
	}
	else if (n == 4)
	{
		double *ptr = new double;
		*ptr = this->_bytesInNew;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Inbound Bytes");
		return (dataToReturn);
	}
	else if (n == 5)
	{
		double *ptr = new double;
		*ptr = this->_bytesOutNew;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Outbound Bytes");
		return (dataToReturn);	
	}
	else if (n == 6)
	{
		long int *ptr = new long int;
		*ptr = this->_packetInNew;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Inbound Packets");
		return (dataToReturn);
	}
	else if (n == 7)
	{
		long int *ptr = new long int;
		*ptr = this->_packetOutNew;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Outbound Packets");
		return (dataToReturn);
	}
	else if (n == 8)
	{
		double *ptr = new double;
		*ptr = this->_bytesInOld;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Inbound Bytes (Previous update)");
		return (dataToReturn);
	}
	else if (n == 9)
	{
		double *ptr = new double;
		*ptr = this->_bytesOutOld;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(DOUBLE);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Outbound Bytes (Previous update)");
		return (dataToReturn);	
	}
	else if (n == 10)
	{
		long int *ptr = new long int;
		*ptr = this->_packetInOld;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Inbound Packets (Previous update)");
		return (dataToReturn);
	}
	else if (n == 11)
	{
		long int *ptr = new long int;
		*ptr = this->_packetOutOld;
		dataToReturn.setDataAddr(ptr);
		dataToReturn.setDataType(LONGINT);
		dataToReturn.setDisplayType(VALUE);
		dataToReturn.setVarLabel("Outbound Packets (Previous update)");
		return (dataToReturn);
	}
	else
		return (dataToReturn);
}

double				NetworkModule::getBytesInDiff(void)		const			{ return (this->_bytesInDiff); }
double				NetworkModule::getBytesOutDiff(void)	const			{ return (this->_bytesOutDiff); }
long int			NetworkModule::getPacketInDiff(void)	const			{ return (this->_packetInDiff); }
long int			NetworkModule::getPacketOutDiff(void)	const			{ return (this->_packetOutDiff); }
double				NetworkModule::getBytesInNew(void)		const			{ return (this->_bytesInNew); }
double				NetworkModule::getBytesOutNew(void)		const			{ return (this->_bytesOutNew); }
long int			NetworkModule::getPacketInNew(void)		const			{ return (this->_packetInNew); }
long int			NetworkModule::getPacketOutNew(void)	const			{ return (this->_packetOutNew); }
double				NetworkModule::getBytesInOld(void)		const			{ return (this->_bytesInOld); }
double				NetworkModule::getBytesOutOld(void)		const			{ return (this->_bytesOutOld); }
long int			NetworkModule::getPacketInOld(void)		const			{ return (this->_packetInOld); }
long int			NetworkModule::getPacketOutOld(void)	const			{ return (this->_packetOutOld); }

void				NetworkModule::setBytesInDiff(double bytesInDiff) 		{ this->_bytesInDiff = bytesInDiff; }
void				NetworkModule::setBytesOutDiff(double bytesOutDiff) 	{ this->_bytesOutDiff = bytesOutDiff; }
void				NetworkModule::setPacketInDiff(long int packetInDiff) 	{ this->_packetInDiff = packetInDiff; }
void				NetworkModule::setPacketOutDiff(long int packetOutDiff) { this->_packetOutDiff = packetOutDiff; }
void				NetworkModule::setBytesInNew(double bytesInNew) 		{ this->_bytesInNew = bytesInNew; }
void				NetworkModule::setBytesOutNew(double bytesOutNew) 		{ this->_bytesOutNew = bytesOutNew; }
void				NetworkModule::setPacketInNew(long int packetInNew) 	{ this->_packetInNew = packetInNew; }
void				NetworkModule::setPacketOutNew(long int packetOutNew) 	{ this->_packetOutNew = packetOutNew; }
void				NetworkModule::setBytesInOld(double bytesInOld) 		{ this->_bytesInOld = bytesInOld; }
void				NetworkModule::setBytesOutOld(double bytesOutOld) 		{ this->_bytesOutOld = bytesOutOld; }
void				NetworkModule::setPacketInOld(long int packetInOld) 	{ this->_packetInOld = packetInOld; }
void				NetworkModule::setPacketOutOld(long int packetOutOld) 	{ this->_packetOutOld = packetOutOld; }

/*int		main(void)
{
	NetworkModule	io(true, 0, "aiou", 0, 0);

	io.updateSysInfo();
	std::cout << *(reinterpret_cast<double*>((io.getData(0)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(1)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(2)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(3)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(4)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(5)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(6)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(7)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(8)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(9)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(10)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(11)).getDataAddr())) << std::endl << std::endl;

	io.updateSysInfo();
	std::cout << *(reinterpret_cast<double*>((io.getData(0)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(1)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(2)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(3)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(4)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(5)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(6)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(7)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(8)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<double*>((io.getData(9)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(10)).getDataAddr())) << std::endl;
	std::cout << *(reinterpret_cast<long int*>((io.getData(11)).getDataAddr())) << std::endl;
	return (0);
}*/




















