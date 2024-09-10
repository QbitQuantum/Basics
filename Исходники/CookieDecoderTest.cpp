TEST(CookieDecoderTest,testDecodingSingleCookieV2) {
    String cookieString = "myCookie=myValue;max-age=50;path=/apathsomewhere;domain=.adomainsomewhere;secure;comment=this is a comment;version=2;commentURL=http://aurl.com;port=\"80,8080\";discard;";
    Set<Cookie> cookies = CookieDecoder.decode(cookieString);
    assertEquals(1, cookies.size());
    Cookie cookie = cookies.iterator().next();
    assertNotNull(cookie);
    assertEquals("myValue", cookie.getValue());
    assertEquals("this is a comment", cookie.getComment());
    assertEquals("http://aurl.com", cookie.getCommentUrl());
    assertEquals(".adomainsomewhere", cookie.getDomain());
    assertTrue(cookie.isDiscard());
    assertEquals(50, cookie.getMaxAge());
    assertEquals("/apathsomewhere", cookie.getPath());
    assertEquals(2, cookie.getPorts().size());
    assertTrue(cookie.getPorts().contains(80));
    assertTrue(cookie.getPorts().contains(8080));
    assertTrue(cookie.isSecure());
    assertEquals(2, cookie.getVersion());
}