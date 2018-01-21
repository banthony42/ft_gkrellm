/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RamModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:39:13 by mgras             #+#    #+#             */
/*   Updated: 2018/01/21 15:15:21 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RamModule.hpp"

RamModule::RamModule(RamModule const &copy): AModule(copy) {
    *this = copy;
}

RamModule::RamModule(void): AModule() {
    return ;
}

RamModule const &RamModule::operator=(RamModule const &copy) {
    return copy;
}

RamModule::RamModule(bool isActive, int ID, std::string name, int position, int len):
        AModule(isActive, ID, name, position, len),
        _mem_size(0),       _usable_memory(0),  _unused_memory(0),
        _used_memory(0),    _virtual_mem(0),    _app_mem(0),
        _cached_files(0),   _wired_memory(0),   _compress_mem(0),
        _memsize(0),        _swapusage(0),      _vmstat(0)
{
    return;
}

RamModule::~RamModule(void) {
    if (this->_vmstat != 0)
        delete this->_vmstat;
    if (this->_swapusage != 0)
        delete this->_swapusage;
    return ;
}

void RamModule::updateSysInfo(void)
{
    if (this->_vmstat != 0)
        delete this->_vmstat;
    if (this->_swapusage != 0)
        delete this->_swapusage;

    this->_vmstat = new vm_statistics64_data_t;
    this->_swapusage = new xsw_usage;

    size_t sizeMem = sizeof(uint64_t);
    size_t sizeSwap = sizeof(xsw_usage);
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    vm_size_t pagesize = 0;
    host_page_size(mach_host_self(), &pagesize);
    try
    {
        if (sysctlbyname("hw.memsize", &this->_memsize, &sizeMem, 0, 0) < 0)
            throw std::exception();
        this->_mem_size = this->_memsize / (1024 * 1024);

        if (sysctlbyname("vm.swapusage", this->_swapusage, &sizeSwap, 0, 0) < 0)
            throw std::exception();

        if(KERN_SUCCESS != host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info_t)this->_vmstat, &count))
            throw std::exception();



        //TOP
        this->_usable_memory = static_cast <uint64_t> (this->_memsize - ((*this->_vmstat).free_count * pagesize));
        this->_unused_memory = static_cast <uint64_t> ((*this->_vmstat).free_count * pagesize);

        //ACTIVITY MONITOR
        this->_virtual_mem =    static_cast <double> (this->_memsize +
                                static_cast <double> ((*this->_vmstat).total_uncompressed_pages_in_compressor * pagesize));

        this->_app_mem = static_cast <double>        ((*this->_vmstat).internal_page_count * pagesize);
        this->_cached_files = static_cast <double>   ((*this->_vmstat).external_page_count * pagesize);
        this->_wired_memory = static_cast <double>   ((*this->_vmstat).wire_count * pagesize);
        this->_compress_mem = static_cast <double>   ((*this->_vmstat).compressor_page_count * pagesize);
        this->_used_memory = this->_app_mem + this->_wired_memory + this->_compress_mem;
    }
    catch (std::exception const &e)
    {
        std::cout << "ERROR_RAM_INFO:" << e.what() << std::endl;
    }
}

DataStruct const RamModule::getData(unsigned int n) const
{
    DataStruct dataToReturn;
    if (n == 0) {
        dataToReturn.setDataAddr(new uint64_t(this->_mem_size));
        dataToReturn.setDataType(UINT64);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Amount of RAM");
        return (dataToReturn);
    }
    else if (n == 1) {
        dataToReturn.setDataAddr(new uint64_t(this->_usable_memory));
        dataToReturn.setDataType(UINT64);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Usable RAM");
        return (dataToReturn);
    }
    else if (n == 2) {
        dataToReturn.setDataAddr(new uint64_t(this->_unused_memory));
        dataToReturn.setDataType(UINT64);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Unused RAM");
        return (dataToReturn);
    }
    else if (n == 3) {
        dataToReturn.setDataAddr(new double(this->_used_memory));
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Used RAM");
        return (dataToReturn);
    }
    else if (n == 4) {
        dataToReturn.setDataAddr(new double(this->_virtual_mem));
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Virtual Memory");
        return (dataToReturn);
    }
    else if (n == 5) {
        dataToReturn.setDataAddr(new double(this->_app_mem));
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Application Memory");
        return (dataToReturn);
    }
    else if (n == 6) {
        double *ptr = new double[sizeof(this->_cached_files)];
        *ptr = this->_cached_files;
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Cached Files");
        return (dataToReturn);
    }
    else if (n == 7) {
        dataToReturn.setDataAddr(new double(this->_wired_memory));
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Wired RAM");
        return (dataToReturn);
    }
    else if (n == 8) {
        dataToReturn.setDataAddr(new double(this->_compress_mem));
        dataToReturn.setDataType(DOUBLE);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Compressed RAM");
        return (dataToReturn);
    }
    else if (n == 9) {
        dataToReturn.setDataAddr(new uint64_t(this->_memsize););
        dataToReturn.setDataType(UINT64);
        dataToReturn.setDisplayType(VALUE);
        dataToReturn.setVarLabel("Total Raw Amount of RAM");
        return (dataToReturn);
    }
    else if (n == 10) {
        if (this->_swapusage == 0)
            return (dataToReturn);
        xsw_usage *ptr = new xsw_usage[sizeof(this->_swapusage)];
        *ptr = *(this->_swapusage);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(XSWUSAGE);
        dataToReturn.setDisplayType(XSW_USAGE);
        dataToReturn.setVarLabel("Swap Usage Structure");
        return (dataToReturn);
    }
    else if (n == 11) {
        if (this->_vmstat == 0)
            return (dataToReturn);
        vm_statistics64_data_t *ptr = new vm_statistics64_data_t[sizeof(this->_vmstat)];
        *ptr = *(this->_vmstat);
        dataToReturn.setDataAddr(ptr);
        dataToReturn.setDataType(VMSTAT64);
        dataToReturn.setDisplayType(VM_STAT64);
        dataToReturn.setVarLabel("Virtual Memory Structure");
        return (dataToReturn);
    }
    return (dataToReturn);
}

uint64_t RamModule::get_mem_size() const
{
    return _mem_size;
}

uint64_t RamModule::get_usable_memory() const
{
    return _usable_memory;
}

uint64_t RamModule::get_unused_memory() const
{
    return _unused_memory;
}

double RamModule::get_used_memory() const
{
    return _used_memory;
}

double RamModule::get_virtual_mem() const
{
    return _virtual_mem;
}

double RamModule::get_app_mem() const
{
    return _app_mem;
}

double RamModule::get_cached_files() const
{
    return _cached_files;
}

double RamModule::get_wired_memory() const
{
    return _wired_memory;
}

double RamModule::get_compress_mem() const
{
    return _compress_mem;
}

uint64_t RamModule::get_memsize() const
{
    return _memsize;
}

xsw_usage *RamModule::get_swapusage() const
{
    return _swapusage;
}

vm_statistics64_data_t *RamModule::get_vmstat() const
{
    return _vmstat;
}