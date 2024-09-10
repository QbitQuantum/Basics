void dcl(StringBuffer &bin, StringList &vout) { // 선언자를 분석하고 결과 출력
    // declarator: * direct-declarator (1)
    int pointer_count = 0;
    char ch;
    while (bin.is_empty() == false) { // 버퍼에 문자가 남아있는 동안
        ch = bin.getc(); // 문자를 획득하고 확인한다
        if (ch == '*') { // *라면 그만큼 포인터를 출력하기 위해
            ++pointer_count; // 카운터를 증가시킨다
        }
        else { // *가 아니라면 포인터를 되돌리고 탈출한다
            bin.ungetc();
            break;
        }
    }
    // declarator: * direct-declarator (2)
    dirdcl(bin, vout); // *을 모두 획득했으므로 직접 선언자를 분석한다
    while (pointer_count > 0) { // 선언자의 분석이 오른쪽에서 먼저 진행되므로
        vout.push_back("*"); // 왼쪽에서 획득한 기호를 오른쪽의 분석이
        --pointer_count; // 종료된 후에 출력해야 한다
    }
}