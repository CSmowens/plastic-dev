////////////////////////////////////////////////////////////
// Copyright (c) 2011 - 2012 Hiairrassary Victor
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of its 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////

namespace plt
{
    template<typename T>
    inline IndexBufferFormatted<T>::IndexBufferFormatted
    (
        const std::vector<T> &indexDatas
    ) :
    m_indexDatas(indexDatas),
    m_indexSize(sizeof(T))
    {

    }


    template<typename T>
    inline IndexBufferFormatted<T>::IndexBufferFormatted
    (
        std::vector<T> &&indexDatas
    ) :
    m_indexDatas(std::move(indexDatas)),
    m_indexSize(sizeof(T))
    {

    }


    template<typename T>
    inline const void* IndexBufferFormatted<T>::getIndexRawData
    (
    ) const
    {
        return &m_indexDatas[0];
    }


    template<typename T>
    inline unsigned int IndexBufferFormatted<T>::getIndexCount
    (
    ) const
    {
        return m_indexDatas.size();
    }


    template<typename T>
    inline unsigned int IndexBufferFormatted<T>::getIndexSize
    (
    ) const
    {
        return m_indexSize;
    }

} // namespace plt
