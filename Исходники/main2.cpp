uberzahl chineseModExp2(uberzahl c, uberzahl a, uberzahl p, uberzahl q){ 
	//a^c mod pq
	auto start = chrono::steady_clock::now();
	
	uberzahl dp = c % (p-1);
	uberzahl dq = c % (q-1);

	uberzahl T = q.inverse(p);
	uberzahl S = p.inverse(q);

	uberzahl m1 = originalModExp(dp,a,p,1);
	uberzahl m2 = originalModExp(dq,a,q,1);
    
	uberzahl m = (m1*q*T + m2*p*S) % (p*q);

	auto current = chrono::steady_clock::now();
	auto elapsed = chrono::duration_cast<chrono::duration<double>>(current-start);
	double chrono_time = elapsed.count();
	cerr << "\tSqMult_CRT time: " << chrono_time << "\n"; 
    
	return m;
}