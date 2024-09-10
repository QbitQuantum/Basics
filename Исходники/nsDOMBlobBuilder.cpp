NS_IMETHODIMP
nsDOMMultipartBlob::MozSlice(PRInt64 aStart, PRInt64 aEnd,
                             const nsAString& aContentType,
                             PRUint8 optional_argc,
                             nsIDOMBlob **aBlob)
{
    nsresult rv;
    *aBlob = nsnull;

    // Truncate aStart and aEnd so that we stay within this file.
    PRUint64 thisLength;
    rv = GetSize(&thisLength);
    NS_ENSURE_SUCCESS(rv, rv);

    if (!optional_argc) {
        aEnd = (PRInt64)thisLength;
    }

    // Modifies aStart and aEnd.
    ParseSize((PRInt64)thisLength, aStart, aEnd);

    // If we clamped to nothing we create an empty blob
    nsTArray<nsCOMPtr<nsIDOMBlob> > blobs;

    PRUint64 length = aEnd - aStart;
    PRUint64 skipStart = aStart;

    NS_ABORT_IF_FALSE(PRUint64(aStart) + length <= thisLength, "Er, what?");

    // Prune the list of blobs if we can
    PRUint32 i;
    for (i = 0; length && skipStart && i < mBlobs.Length(); i++) {
        nsIDOMBlob* blob = mBlobs[i].get();

        PRUint64 l;
        rv = blob->GetSize(&l);
        NS_ENSURE_SUCCESS(rv, rv);

        if (skipStart < l) {
            PRUint64 upperBound = NS_MIN<PRUint64>(l - skipStart, length);

            nsCOMPtr<nsIDOMBlob> firstBlob;
            rv = mBlobs.ElementAt(i)->MozSlice(skipStart, skipStart + upperBound,
                                               aContentType, 2,
                                               getter_AddRefs(firstBlob));
            NS_ENSURE_SUCCESS(rv, rv);

            // Avoid wrapping a single blob inside an nsDOMMultipartBlob
            if (length == upperBound) {
                firstBlob.forget(aBlob);
                return NS_OK;
            }

            blobs.AppendElement(firstBlob);
            length -= upperBound;
            i++;
            break;
        }
        skipStart -= l;
    }

    // Now append enough blobs until we're done
    for (; length && i < mBlobs.Length(); i++) {
        nsIDOMBlob* blob = mBlobs[i].get();

        PRUint64 l;
        rv = blob->GetSize(&l);
        NS_ENSURE_SUCCESS(rv, rv);

        if (length < l) {
            nsCOMPtr<nsIDOMBlob> lastBlob;
            rv = mBlobs.ElementAt(i)->MozSlice(0, length, aContentType, 2,
                                               getter_AddRefs(lastBlob));
            NS_ENSURE_SUCCESS(rv, rv);

            blobs.AppendElement(lastBlob);
        } else {
            blobs.AppendElement(blob);
        }
        length -= NS_MIN<PRUint64>(l, length);
    }

    // we can create our blob now
    nsCOMPtr<nsIDOMBlob> blob = new nsDOMMultipartBlob(blobs, aContentType);
    blob.forget(aBlob);
    return NS_OK;
}