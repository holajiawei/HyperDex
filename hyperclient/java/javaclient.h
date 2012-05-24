// Copyright (c) 2012, Cornell University
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of HyperDex nor the names of its contributors may be
//       used to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef hyperclient_javaclient_h_
#define hyperclient_javaclient_h_

// HyperClient
#include "../hyperclient.h"

class HyperType
{
    public:
        HyperType();
        virtual ~HyperType() throw ();

        virtual hyperdatatype type() const;
        virtual void serialize(std::string& value) const;
        static HyperType* deserialize(const hyperclient_attribute& attr);
        virtual int data(char *bytes, int len);
        virtual std::string toString();
};

class HyperString : public HyperType
{
    public:
        HyperString(const std::string& attr_value);
        HyperString(const char *s, size_t n);
        virtual ~HyperString() throw ();

    private:
        std::string m_attr_value;
        
    public:
        virtual hyperdatatype type() const;
        virtual void serialize(std::string& value) const;
        virtual int data(char *bytes, int len);
        virtual std::string toString();
};

class HyperInteger : public HyperType
{
    public:
        HyperInteger(int64_t attr_value);
        virtual ~HyperInteger() throw ();

    private:
        int64_t m_attr_value;

    public:

        virtual hyperdatatype type() const;
        virtual void serialize(std::string& value) const;
        virtual int data(char *bytes, int len);
        virtual std::string toString();
};

class HyperMap : public HyperType
{
    public:
        HyperMap();
        HyperMap(const HyperMap& hypermap);
        virtual ~HyperMap() throw ();

    private:
        std::map<std::string,HyperType*> m_map;
        hyperdatatype m_type;

        void destr_clear() throw();
        void destr_del(const std::string& key) throw (std::out_of_range);

        
    public:
        virtual hyperdatatype type() const;
        virtual void serialize(std::string& value) const;
        virtual int data(char *bytes, int len);
        virtual std::string toString();

        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef std::string key_type;
        typedef HyperMap* mapped_type;

        unsigned int size() const;
        bool empty() const;
        void clear();
        const HyperType* get(const std::string& key) throw (std::out_of_range);
        void set(const std::string&, HyperType* value);
        void del(const std::string& key) throw (std::out_of_range);
        bool has_key(const std::string& key);

        void insert(const std::string&, HyperType* value);
        std::map<std::string,HyperType*>::const_iterator begin() const;
        std::map<std::string,HyperType*>::const_iterator end() const;

};

class HyperClient
{
    public:
        HyperClient(const char* coordinator, in_port_t port);
        ~HyperClient() throw ();

    public:
        hyperclient_returncode get(const std::string& space,
                       const std::string& key,
                       HyperMap *values);

        hyperclient_returncode put(const std::string& space,
                       const std::string& key,
                       const HyperMap& attributes);

        hyperclient_returncode del(const std::string& space,
                       const std::string& key);
        hyperclient_returncode range_search(const std::string& space,
                                const std::string& attr,
                                int64_t lower,
                                int64_t upper,
                                std::vector<HyperMap*> *results);

    private:
        hyperclient m_client;
};

#endif // hyperclient_javaclient_h_
