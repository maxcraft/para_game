#pragma once
#include <raylib.h>

#include <vector>
#include <cstdlib>
#include <string>

namespace Game
{
    template< typename T >
    class Entities
    {
        public:
            Entities( size_t capacity = 10000, size_t collections = 1 )
            : m_lists( collections )
            {
                m_pool = static_cast< Item * >( malloc( capacity * sizeof( Item ) ) );
                m_freeHead = m_pool;

                for( size_t i = 0; i < capacity; ++i )
                {
                    m_pool[ i ].next = m_pool + i + 1;
                    m_pool[ i ].prev = m_pool + i - 1;
                }

                m_pool[ capacity - 1 ].next = nullptr;
                m_pool[ 0 ].prev = nullptr;
            }

            ~Entities()
            {
                free( m_pool );
            }

            template< class... Args >
            void spawn( Args... args )
            {
                if( !m_freeHead ) return;

                Item *p = m_freeHead;

                m_freeHead = p->next;

                if( m_freeHead ) m_freeHead->prev = nullptr;
                
                p = new( p ) Item( args... );

                add( p, m_lists[ 0 ] );
            }

            template< class... Args >
            void draw( float time, Args... args )
            {
                // size_t number = 0;

                for( auto &head : m_lists )
                {
                    for( Item *p = head, *n = nullptr; p; p = n )
                    {
                        n = p->next;
                        if( !p->draw( time, args... ) )
                        {
                            destroy( p );
                        }

                        // ++number;
                    }
                }

                // std::string txt = "Entities number: " + std::to_string( number );
                // DrawText( txt.c_str(), 0, 0, 20, WHITE );
            }

            
            struct Item : public T
            {
                Item *next;
                Item *prev;

                template< class... Args >
                Item( Args... args )
                : T( args... )
                , next( nullptr )
                , prev( nullptr )
                {}

                ~Item()
                {
                    // next = nullptr;
                    // prev = nullptr;
                }

            };

            void destroy( Item *item )
            {
                if( !item ) return;
                remove( item );

                item->~Item();

                add( item, m_freeHead );

            }

            void change( Item *item, size_t newCollection )
            {
                if( !item && m_lists.size() >= newCollection ) return;
                
                remove( item );
                add( item, m_lists[ newCollection ] );
            }

            Item *detectHit( const Vector2 &position, float radius )
            {
                for( Item *p = m_lists[ 0 ]; p ; p = p->next )
                {
                    if( p->isHit( position, radius ) ) return p;
                }

                return nullptr;
            }

            bool empty()
            {
                for( auto &i : m_lists )
                {
                    if( i )
                    {
                        return false;
                    }
                }

                return true;
            }

        private:
            std::vector< Item * > m_lists;
            Item *m_pool;
            Item *m_freeHead;

            void remove( Item *item )
            {
                if( !item ) return;

                Item *prev = item->prev, *next = item->next;

                if( prev ) 
                {
                    prev->next = next;
                }
                else
                {
                    for( size_t i = 0, c = m_lists.size(); i < c; ++i )
                    {
                        if( m_lists[ i ] == item )
                        {
                            m_lists[ i ] = next;
                            break;
                        }
                    }
                }

                if( next ) next->prev = prev;
            }

            void add( Item *item, Item *&head )
            {
                if( head ) head->prev = item;

                item->next = head;
                item->prev = nullptr;
                head = item;
            }
    };
} // namespace Game
