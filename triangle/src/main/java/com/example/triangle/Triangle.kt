package com.example.triangle

import android.util.Log
import androidx.annotation.Keep

class Triangle{


    external fun draw(width: Float, height: Float, scale: Float, angle: Float)
    external fun onRadSet(rad: Float)

    @Keep
    private fun updateRad(str: String){
        Log.d("~~~~~ handler", str)
    }

    companion object {
        init {
            System.loadLibrary("Triangle")
        }
    }
}

interface OnRadSetListener {

    fun onRadSetCall(rad: Float)
}