/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RamModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:22:17 by banthony          #+#    #+#             */
/*   Updated: 2018/01/20 16:22:17 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAMMODULE_HPP
# define RAMMODULE_HPP

# include "AModule.hpp"

# include <sys/types.h>
# include <sys/sysctl.h>
# include <mach/vm_statistics.h>

/*
**  Nom d'attribut avec underscore: valeurs pré-calculées en bytes
**  Nom d'attribut sans underscore: valeurs brut
**
*/

class RamModule: public AModule {
    private:
    uint64_t                _mem_size;
    uint64_t                _usable_memory;
    uint64_t                _unused_memory;
    double                  _used_memory;
    double                  _virtual_mem;
    double                  _app_mem;
    double                  _cached_files;
    double                  _wired_memory;
    double                  _compress_mem;

    uint64_t                _memsize;
    xsw_usage               *_swapusage;
    vm_statistics64_data_t  *_vmstat;

    RamModule(void);
    RamModule(RamModule const &copy);
    RamModule const & operator=(RamModule const &copy);

    public:
    RamModule(bool isActive, int ID, std::string name, int position, int len);
    virtual ~RamModule(void);

    virtual void        updateSysInfo(void);
    virtual DataStruct  const getData(unsigned int n) const;

    uint64_t get_mem_size() const;

    uint64_t get_usable_memory() const;

    uint64_t get_unused_memory() const;

    double get_used_memory() const;

    double get_virtual_mem() const;

    double get_app_mem() const;

    double get_cached_files() const;

    double get_wired_memory() const;

    double get_compress_mem() const;

    uint64_t get_memsize() const;

    xsw_usage *get_swapusage() const;

    vm_statistics64_data_t *get_vmstat() const;
};


#endif //RUSH_01_CPP_RAMMODULE_HPP