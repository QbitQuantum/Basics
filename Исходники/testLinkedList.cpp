        int main( )
        {
            List<int>    theList;
            ListItr<int> theItr = theList.zeroth( );
            int i;

            printList( theList );

            for( i = 0; i < 10; i++ )
            {
                theList.insert( i, theItr );
                printList( theList );
                theItr.advance( );
            }

            for( i = 0; i < 10; i += 2 )
                theList.remove( i );

            for( i = 0; i < 10; i++ )
                if( ( i % 2 == 0 ) != ( theList.find( i ).isPastEnd( ) ) )
                    cout << "Find fails!" << endl;

            cout << "Finished deletions" << endl;
            printList( theList );

            List<int> list2;
            list2 = theList;
            printList( list2 );

            return 0;
        }